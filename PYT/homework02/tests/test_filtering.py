#!/usr/bin/env python3
# -*- coding: utf-8 -*-
import ast
import inspect
from pathlib import Path
import pytest
from pylint.lint import Run
from pylint.reporters import CollectingReporter
from numpy.testing import assert_equal
import numpy as np
from filtering.helpers import read_image, identity_kernel, approx_gaussian_blur_5_kernel, edge_detection_kernel, \
    roberts_cross_1_kernel, roberts_cross_2_kernel
from filtering.filtering import apply_filter


@pytest.fixture(scope="session")
def image():
    """ Loads base and overused image """
    return read_image('tests/lenna.png')


@pytest.fixture(scope="session")
def image_gaussian_blur():
    """ Loads blurred image """
    return read_image('tests/lenna_gaussian_blur.png')


@pytest.fixture(scope="session")
def image_gray(image):
    """ Loads gray image """
    return np.average(image.astype(float), weights=[0.299, 0.587, 0.114], axis=2).astype(np.uint8)


@pytest.fixture(scope="session")
def image_gray_edge_detection():
    """ Loads image for edge detection """
    return read_image('tests/lenna_gray_edge_detection.png')


@pytest.fixture(scope="session")
def image_roberts_cross():
    """ Loads image with roverts cross kernel applied """
    return read_image('tests/lenna_roberts_cross.png')


@pytest.fixture(scope="session")
def linter():
    """ Test codestyle for src file of render_tree fucntion. """
    src_file = inspect.getfile(apply_filter)
    rep = CollectingReporter()
    # disabled warnings:
    # 0301 line too long
    # 0103 variables name (does not like shorter than 2 chars)
    r = Run(['--disable=C0301,C0103 ', '-sn', src_file], reporter=rep, exit=False)
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


def test_only_numpy_import_allowed():
    """ Test if no external modeles is used. """
    src_file = inspect.getfile(apply_filter)
    modules, names = get_imports(source_file=src_file, recursive=True)
    print(f'modules={modules}, names={names}')
    assert len(modules) <= 1
    assert len(names) == 0
    if len(modules) == 1:
        assert modules[0] == 'numpy'


def test_identity_filter(image):
    """ Test simple identity kernel """
    assert_equal(image, apply_filter(image, identity_kernel))


def test_gaussian_blur(image, image_gaussian_blur):
    """ Test gaussian bluer kernel """
    assert_equal(apply_filter(image, approx_gaussian_blur_5_kernel), image_gaussian_blur)


def test_gray_edge_detection(image_gray, image_gray_edge_detection):
    """ Test edge detection kernel """
    assert_equal(apply_filter(image_gray, edge_detection_kernel), image_gray_edge_detection)


def test_roberts_cross_operator(image_gray, image_roberts_cross):
    """ Test roberts cross kernel """
    assert_equal(
        apply_filter(apply_filter(image_gray, roberts_cross_1_kernel), roberts_cross_2_kernel),
        image_roberts_cross)
