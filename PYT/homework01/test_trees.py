#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
@author: Martin Slapak
"""

import ast
import inspect
from pathlib import Path
import pytest
from pylint.lint import Run
from pylint.reporters import CollectingReporter
from trees import render_tree


def get_imports(source=None, source_file=None, modules=None, names=None, recursive=False):
    """ Traverse source and pick imports. """
    # print(f'DIG {source_file}')
    if source is None and source_file is None:
        raise Exception('At least source or source_file must not be None.')

    if source is not None:
        a = ast.parse(source)
    else:
        a = ast.parse(Path(source_file).read_text())

    if modules is None:
        modules = []
    if names is None:
        names = []

    for node in ast.walk(a):
        if isinstance(node, ast.ImportFrom):
            modules += [node.module]
            names += [f'{node.module}.{item.name}' for item in node.names]

        if isinstance(node, ast.Import):
            modules += [item.name for item in node.names]

    # fake recursion thanx to the appending to the end of modules list,
    # the newly explored imports will be processed in the same for-loop
    if recursive:
        for m in modules:
            if Path(f'{m}.py').exists():
                # print(f'{m}.py existuje....')
                get_imports(source=None, source_file=f'{m}.py', modules=modules, names=names, recursive=False)

    return modules, names


@pytest.fixture(scope="session")
def linter():
    """ Test codestyle for src file of render_tree fucntion. """
    src_file = inspect.getfile(render_tree)
    rep = CollectingReporter()
    # disabled warnings:
    # 0301 line too long
    # 0103 variables name (does not like shorter than 2 chars)
    # 0719 too general exception (needed for invalid trees without defining own exception class)
    r = Run(['--disable=C0301,C0103,W0719', '-sn', src_file], reporter=rep, exit=False)
    return r.linter


@pytest.mark.parametrize("limit", range(0, 11))
def test_codestyle_score(linter, limit, runs=[]):
    """ Evaluate codestyle for different thresholds. """
    if len(runs) == 0:
        print('\nLinter output:')
        for m in linter.reporter.messages:
            print(f'{m.msg_id} ({m.symbol}) line {m.line}: {m.msg}')
    runs.append(limit)
    # score = linter.stats['global_note']
    score = linter.stats.global_note

    print(f'pylint score = {score} limit = {limit}')
    assert score >= limit


def test_no_imports_allowed():
    """ Test if no external modeles is used. """
    src_file = inspect.getfile(render_tree)
    modules, names = get_imports(source_file=src_file, recursive=True)
    # print(modules, names)
    assert len(modules) == 0
    assert len(names) == 0


def test_invalid_tree():
    """ Test if raised exception on invalid input. """
    x = [5, 6, 7, 8, 9]
    # print(x)
    with pytest.raises(Exception) as e_info:
        render_tree(x)
    assert str(e_info.value) == 'Invalid tree'


@pytest.mark.parametrize(
    "indent, separator, tree, expected", [
        (4, '.', [[[1, [True, ['abc', 'def']]], [2, [3.14159, 6.023e23]]], 42], '42\n├──>1\n│...└──>True\n│.......├──>abc\n│.......└──>def\n└──>2\n....├──>3.14159\n....└──>6.023e+23\n'),
        (4, '.', [[[1, [[True, ['abc', 'def']], [False, [1, 2]]]], [2, [3.14159, 6.023e23, 2.718281828]], [3, ['x', 'y']], [4, []]], 42], '42\n├──>1\n│...├──>True\n│...│...├──>abc\n│...│...└──>def\n│...└──>False\n│.......├──>1\n│.......└──>2\n├──>2\n│...├──>3.14159\n│...├──>6.023e+23\n│...└──>2.718281828\n├──>3\n│...├──>x\n│...└──>y\n└──>4\n'),
        (2, ' ', [6, [[[[1, [2, 3]], [42, [-43, 44]]], 4], 5]], '6\n└>5\n  └>4\n    ├>1\n    │ ├>2\n    │ └>3\n    └>42\n      ├>-43\n      └>44\n'),
        (2, ' ', [6, [5, ['dva\nradky']]], '6\n└>5\n  └>dva\nradky\n'),
    ],
)
def test_examples_from_assignment(indent, separator, tree, expected):
    """ Test set of trees from assignment. """
    ret = render_tree(tree, indent=indent, separator=separator)
    assert ret == expected


@pytest.mark.parametrize(
    "tree, expected", [
        ([1, [2]], '1\n└>2\n'),
        ([1, [2, [3, [4, 5]]]], '1\n└>2\n  └>3\n    ├>4\n    └>5\n'),
        ([[[1, [2, 3]], 4], 5], '5\n└>4\n  └>1\n    ├>2\n    └>3\n'),
        ([6, [[[[1, [2, 3]], [42, [-43, 44]]], 4], 5]], '6\n└>5\n  └>4\n    ├>1\n    │ ├>2\n    │ └>3\n    └>42\n      ├>-43\n      └>44\n'),
        ([4, [5, 6, 7, 8, 9]], '4\n├>5\n├>6\n├>7\n├>8\n└>9\n'),
    ],
)
def test_basic_tree(tree, expected):
    """ Set of basic tests. """
    ret = render_tree(tree, indent=2, separator=' ')
    oo = ret.replace('\n', '\\n')
    print(f'expected= ({tree}, \'{oo}\')')
    assert ret == expected


@pytest.mark.parametrize(
    "tree, expected", [
        (['a', ['b']], 'a\n└>b\n'),
        ([1, [3.14]], '1\n└>3.14\n'),
        (['bagr', ['lopata', 'rameno']], 'bagr\n├>lopata\n└>rameno\n'),
        (['bagr', ['lopata', 'ram\neno']], 'bagr\n├>lopata\n└>ram\neno\n'),
        ([{'key': 'val'}, [(1, 2, 3, 4, 5), None]], '{\'key\': \'val\'}\n├>(1, 2, 3, 4, 5)\n└>None\n'),
    ],
)
def test_noninteger_tree(tree, expected):
    """ Set of advanced non-integer trees. """
    ret = render_tree(tree, indent=2, separator=' ')
    assert ret == expected


@pytest.mark.parametrize(
    "indent, separator, expected", [
        (2, '.', '3\n├>1\n│.└>2\n│...├>4\n│...└>5\n└>42\n..├>43\n..└>44\n'),
        (3, '.', '3\n├─>1\n│..└─>2\n│.....├─>4\n│.....└─>5\n└─>42\n...├─>43\n...└─>44\n'),
        (4, '.', '3\n├──>1\n│...└──>2\n│.......├──>4\n│.......└──>5\n└──>42\n....├──>43\n....└──>44\n'),
        (4, ' ', '3\n├──>1\n│   └──>2\n│       ├──>4\n│       └──>5\n└──>42\n    ├──>43\n    └──>44\n'),
    ],
)
def test_indentsep_tree(indent, separator, expected):
    """ Test set of specific indent and separators. """
    tree = [[[1, [2, [4, 5]]], [42, [43, 44]]], 3]
    ret = render_tree(tree, indent=indent, separator=separator)
    assert ret == expected
