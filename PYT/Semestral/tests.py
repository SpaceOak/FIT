import pytest
import pygame

import main
import settings


class Tester:
    def validate_score_rules(self):
        assert settings.score_target_time > 0
        assert settings.score_per_fruit > 0

    def validate_map(self):
        try:
            with open(settings.map_filename, 'r') as file:
                assert not file.closed

                lines = file.readlines()
                first_line_length = len(lines[0].strip())

                #  each column is equal to each, each line has same length as each
                for line in lines[1:]:
                    assert len(line.strip()) == first_line_length

            file.close()
            assert file.closed
        except IOError:
            print("Map test failed ", file)

    def test_enemy(self):
        enemy = main.Enemy(0, 0)
        assert isinstance(enemy, main.Enemy)
        assert isinstance(enemy.x, int)
        assert isinstance(enemy.y, int)
        assert enemy.direction in ["up", "down", "left", "right"]
        assert enemy.staying_on in main.ObjectType

    def test_search(self):
        assert main.find_object(main.ObjectType.ENEMY) is None

    def run_all(self):
        self.validate_score_rules(self)
        self.validate_map(self)
        self.test_enemy(self)

