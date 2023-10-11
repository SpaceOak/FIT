import pygame
import settings
from enum import Enum
import random


class ObjectType(Enum):
    EMPTY = 0
    PLAYER = 1
    ENEMY = 2
    WALL = 3
    FRUIT = 4
    BOOST_SPEED_UP = 5
    BOOST_SPEED_DOWN = 6
    BOOST_HULK = 7


class Enemy:
    def __init__(self, x, y):
        self.x = x
        self.y = y
        self.direction = random.choice(["up", "down", "left", "right"])
        self.staying_on = ObjectType.FRUIT



class Bonus:
    def __init__(self, x, y, type):
        self.x = x
        self.y = y
        self.type = type


# Spawn and initialize clue objects of the game
def init_screen_and_game():
    global screen, display, clock
    pygame.init()
    pygame.display.set_caption('Game')
    screen = pygame.display.set_mode((settings.SCREEN_WIDTH, settings.SCREEN_HEIGHT), 0, 32)
    clock = pygame.time.Clock()


# Drawing per each segment fo grid
def draw_per_cell():
    # First pass with most data ( player, walls, space and etc )
    for y_segment in range(settings.grid_height):
        for x_segment in range(settings.grid_width):
            x = x_segment * settings.cell_size
            y = y_segment * settings.cell_size
            rect = pygame.Rect(x, y, settings.cell_size, settings.cell_size)
            if grid[y_segment][x_segment] == ObjectType.EMPTY:
                pygame.draw.rect(screen, (255, 255, 255), rect)  # White color for empty cells
            elif grid[y_segment][x_segment] == ObjectType.PLAYER:
                pygame.draw.rect(screen, (0, 255, 0), rect)  # Green color for player
            elif grid[y_segment][x_segment] == ObjectType.ENEMY:
                pygame.draw.rect(screen, (255, 0, 0), rect)  # Red color for enemy
            elif grid[y_segment][x_segment] == ObjectType.WALL:
                pygame.draw.rect(screen, (0, 0, 255), rect)  # Blue color for wall
            elif grid[y_segment][x_segment] == ObjectType.FRUIT:
                pygame.draw.rect(screen, (255, 255, 0), rect)  # Yellow color for fruit

    # Second pass with bonuses only
    for bonus in bonus_list:
        x = bonus.x * settings.cell_size
        y = bonus.y * settings.cell_size
        rect = pygame.Rect(y, x, settings.cell_size, settings.cell_size)
        if bonus.type == ObjectType.BOOST_SPEED_UP:
            pygame.draw.rect(screen, (255, 165, 0), rect)  # Orange color for speed-up boost
        elif bonus.type == ObjectType.BOOST_SPEED_DOWN:
            pygame.draw.rect(screen, (128, 0, 128), rect)  # Purple color for speed-down boost
        elif bonus.type == ObjectType.BOOST_HULK:
            pygame.draw.rect(screen, (255, 20, 147), rect)  # Pink color for Hulk boost


# Not the best way to remove an enemy after destroying it
def remove_enemy_by_coord(x, y):
    e = ObjectType.EMPTY
    for each in enemies:
        if each.x == x and each.y == y:
            e = each
    grid[e.x][e.y] = e.staying_on
    enemies.remove(e)


# Move player and handle all relative collision
def move_player(direction):
    # Do not have a reference of player so have to find it
    player_pos = find_object(ObjectType.PLAYER)
    # In case a player is destroyed by enemies
    if not player_pos:
        loop = False
        return None, False

    # Handle each case of direction
    if direction == "up":
        if grid[player_pos[0] - 1][player_pos[1]] == ObjectType.ENEMY:
            if active_bonus[0] == ObjectType.BOOST_HULK:
                remove_enemy_by_coord(player_pos[0] - 1, player_pos[1])
            else:
                loop = False
                win = False
                return None, False
        new_pos = (player_pos[0] - 1, player_pos[1])

    elif direction == "down":
        if grid[player_pos[0] + 1][player_pos[1]] == ObjectType.ENEMY:
            if active_bonus[0] == ObjectType.BOOST_HULK:
                remove_enemy_by_coord(player_pos[0] + 1, player_pos[1])
            else:
                loop = False
                win = False
                return None, False
        new_pos = (player_pos[0] + 1, player_pos[1])

    elif direction == "left":
        if grid[player_pos[0]][player_pos[1] - 1] == ObjectType.ENEMY:
            if active_bonus[0] == ObjectType.BOOST_HULK:
                remove_enemy_by_coord(player_pos[0], player_pos[1] - 1)
            else:
                loop = False
                win = False
                return None, False
        new_pos = (player_pos[0], player_pos[1] - 1)

    elif direction == "right":
        if grid[player_pos[0]][player_pos[1] + 1] == ObjectType.ENEMY:
            if active_bonus[0] == ObjectType.BOOST_HULK:
                remove_enemy_by_coord(player_pos[0], player_pos[1] + 1)
            else:
                loop = False
                win = False
                return None, False
        new_pos = (player_pos[0], player_pos[1] + 1)

    precalculated_bonus = active_bonus

    # Checking overlapping with each bonus
    for each_bonus in bonus_list:
        if each_bonus.x == player_pos[0] and each_bonus.y == player_pos[1]:
            if each_bonus.type == ObjectType.BOOST_HULK:
                precalculated_bonus = (each_bonus.type, 1.0)
            elif each_bonus.type == ObjectType.BOOST_SPEED_DOWN:
                precalculated_bonus = (each_bonus.type, settings.bonus_speed_down_multiplyer)
            elif each_bonus.type == ObjectType.BOOST_SPEED_UP:
                precalculated_bonus = (each_bonus.type, settings.bonus_speed_up_multiplyer)
            bonus_list.remove(each_bonus)
            break

    # Mark that there is no fruit
    fruit_eleminated = False
    # Check if the new position is within the grid boundaries and not a wall
    if (
            0 <= new_pos[0] < settings.grid_height
            and 0 <= new_pos[1] < settings.grid_width
            and grid[new_pos[0]][new_pos[1]] != ObjectType.WALL
    ):
        grid[player_pos[0]][player_pos[1]] = ObjectType.EMPTY  # Clear current player position
        if grid[new_pos[0]][new_pos[1]] == ObjectType.FRUIT:
            fruit_eleminated = True
        else:
            fruit_eleminated = False
        grid[new_pos[0]][new_pos[1]] = ObjectType.PLAYER  # Move player to the new position

    return precalculated_bonus, fruit_eleminated


def move_enemy(enemy):
    # Remove from the grid
    grid[enemy.x][enemy.y] = enemy.staying_on

    # Update location
    if enemy.direction == "up":
        enemy.x += 1
    elif enemy.direction == "down":
        enemy.x -= 1
    elif enemy.direction == "left":
        enemy.y -= 1
    elif enemy.direction == "right":
        enemy.y += 1

    # End game condition
    if grid[enemy.x][enemy.y] == ObjectType.PLAYER:
        if active_bonus[0] == ObjectType.BOOST_HULK:
            enemies.remove(enemy)
            return
        else:
            loop = False
            win = False
            return

    # Add to the new position on grid
    enemy.staying_on = grid[enemy.x][enemy.y]
    grid[enemy.x][enemy.y] = ObjectType.ENEMY


# Looking for the first object of selected type and return it's coordinates ( actually used for the player )
def find_object(object_type):
    for x in range(settings.grid_height):
        for y in range(settings.grid_width):
            if grid[x][y] == object_type:
                return x, y
    return None


# Load the map according to settings and validate/update all inner variables
# Also handle cases if some map rules are failed
def load_map(filename):
    # Open and read a file
    with open(filename, "r") as file:
        lines = file.readlines()

    # Receive map sizes
    grid_height = len(lines)
    grid_width = len(lines[0].strip())

    amount_of_fruits = 0
    # Make a grid
    grid = [[ObjectType.EMPTY for _ in range(grid_width)] for _ in range(grid_height)]

    # Fill the grid according to the map
    for x, line in enumerate(lines):
        for y, char in enumerate(line.strip()):
            if char == "=" or char == "#":
                grid[x][y] = ObjectType.WALL
            elif char == "p":
                grid[x][y] = ObjectType.PLAYER
            elif char == "e":
                grid[x][y] = ObjectType.ENEMY
                enemies.append(Enemy(x, y))
            elif char == " ":
                grid[x][y] = ObjectType.FRUIT
                amount_of_fruits += 1

    # Shut down game if there are more bonuses than space
    if settings.bonus_count >= amount_of_fruits:
        print("Incorrect settings")
        exit()

    # Check the number of bonuses and add randomly if needed
    bonus_count = sum(1 for row in grid for cell in row if
                      cell in [ObjectType.BOOST_SPEED_UP, ObjectType.BOOST_SPEED_DOWN, ObjectType.BOOST_HULK])
    while bonus_count < settings.bonus_count:
        x = random.randint(0, grid_height - 1)
        y = random.randint(0, grid_width - 1)
        if grid[x][y] == ObjectType.EMPTY:
            bonus_type = random.choice([ObjectType.BOOST_SPEED_UP, ObjectType.BOOST_SPEED_DOWN, ObjectType.BOOST_HULK])
            bonus_list.append(Bonus(x, y, bonus_type))
            grid[x][y] = bonus_type
            bonus_count += 1
        if grid[x][y] == ObjectType.FRUIT:
            bonus_type = random.choice([ObjectType.BOOST_SPEED_UP, ObjectType.BOOST_SPEED_DOWN, ObjectType.BOOST_HULK])
            bonus_list.append(Bonus(x, y, bonus_type))
            grid[x][y] = bonus_type
            bonus_count += 1
            amount_of_fruits -= 1

    return grid, amount_of_fruits


# Inspecting space around object
def is_able_to_go(x, y, direction):
    if direction == "up":
        return grid[x + 1][y] != ObjectType.WALL
    if direction == "down":
        return grid[x - 1][y] != ObjectType.WALL
    if direction == "left":
        return grid[x][y - 1] != ObjectType.WALL
    if direction == "right":
        return grid[x][y + 1] != ObjectType.WALL

# Return all available direction for the selected enemy
def get_available_directions(enemy):
    directions = ["up", "down", "left", "right"]

    #  Checking each direction
    if grid[enemy.x][enemy.y - 1] == ObjectType.WALL or grid[enemy.x][enemy.y - 1] == ObjectType.ENEMY:
        directions.remove("left")
    if grid[enemy.x][enemy.y + 1] == ObjectType.WALL or grid[enemy.x][enemy.y + 1] == ObjectType.ENEMY:
        directions.remove("right")
    if grid[enemy.x + 1][enemy.y] == ObjectType.WALL or grid[enemy.x + 1][enemy.y] == ObjectType.ENEMY:
        directions.remove("up")
    if grid[enemy.x - 1][enemy.y] == ObjectType.WALL or grid[enemy.x - 1][enemy.y] == ObjectType.ENEMY:
        directions.remove("down")

    return directions


# Return amount of enimies that are alive at the end of the game
def remaining_enemies():
    count = 0
    for x in range(settings.grid_height):
        for y in range(settings.grid_width):
            if grid[x][y] == ObjectType.ENEMY:
                count += 1
    return count


# Calculate print and save player score
def handle_score():
    default_score = len(grid) * len(grid[0])

    score = (default_score - amount_of_fruits - remaining_enemies() * 10) * (
                settings.score_target_time / total_timer)
    print(score)

    with open("Content/Score.txt", 'a') as file:
        file.write('\n' + score.__str__())


if __name__ == "__main__":
    # ------------------------MAIN------------------------
    # Initialize internal variables
    move_timer = 0  # Interval timer
    bonus_timer = 0 # Timer of active bonus
    total_timer = 0 # Timer of total amount of time spend in game
    bonus_timer_is_active = False

    last_move_direction = "right"  # Player last movement direction
    enemies = []                   # Array of enemies to be updated
    active_bonus = (ObjectType.EMPTY, 1.0)  # Bonus relative data
    bonus_list = []                         # List of all bonuses located at map

    grid, amount_of_fruits = load_map(settings.map_filename)  # Loading map

    # Updating frid sizes
    settings.grid_width = len(grid[0])
    settings.grid_height = len(grid)
    init_screen_and_game()

    loop = True
    win = True

    # Main game loop
    while loop:
        screen.fill(settings.background_color)
        draw_per_cell()

        # Handle player input
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                loop = False
            elif event.type == pygame.KEYDOWN:
                if event.key == pygame.K_ESCAPE:
                    loop = False
                    win = False
                elif event.key == pygame.K_UP or event.key == pygame.K_w:
                    last_move_direction = "up"
                elif event.key == pygame.K_DOWN or event.key == pygame.K_s:
                    last_move_direction = "down"
                elif event.key == pygame.K_LEFT or event.key == pygame.K_a:
                    last_move_direction = "left"
                elif event.key == pygame.K_RIGHT or event.key == pygame.K_d:
                    last_move_direction = "right"

        # Move by interval
        move_timer += clock.get_time() / 1000  # Specific way to convert the time
        total_timer += clock.get_time() / 1000
        if active_bonus[0] != (ObjectType.EMPTY):
            bonus_timer += clock.get_time() / 1000

        new_move_interval = settings.move_interval * active_bonus[1]

        # Condition to manipulate with game speed
        if move_timer >= new_move_interval:
            state_tmp = active_bonus
            active_bonus, removed_fruit = move_player(last_move_direction)  # Move player
            if removed_fruit:
                amount_of_fruits -= 1
                if not amount_of_fruits:
                    break
            if active_bonus is None:
                win = False
                break
            if active_bonus[0] != state_tmp:
                bonus_timer_is_active = True
            if bonus_timer > settings.bonus_interval:
                bonus_timer = 0
                active_bonus = (ObjectType.EMPTY, 1.0)
                bonus_timer_is_active = False
            move_timer = 0  # Reset timer
            for enemy in enemies:
                if not is_able_to_go(enemy.x, enemy.y, enemy.direction) or len(get_available_directions(enemy)) != 2:
                    if get_available_directions(enemy):
                        enemy.direction = random.choice(get_available_directions(enemy))
                    else:
                        remove_enemy_by_coord(enemy.x, enemy.y)
                move_enemy(enemy)
                if not win:
                    break

        clock.tick(settings.target_fps)
        pygame.display.flip()

    # ------------------------END------------------------
    pygame.quit()
    if win:
        print("You win")
    else:
        print("Better luck next time")

    handle_score()
