from collections import namedtuple
import time # measuring time

#Define universal gravitation constant
G=6.67408e-11 #N-m2/kg2
SpaceObject = namedtuple('SpaceObject', 'name mass x y vx vy color')
Force = namedtuple('Force', 'fx fy')

def logging(unit='ms'):
    def decorator(func):
        coef = 1
        def helper(*args, **kwargs):
            if unit is 'ms':
                coef = 1000
            start = int(round(time.time() * coef))
            helper.calls += 1
            try:
                return func(*args, **kwargs)
            finally:
                end_ = int(round(time.time() * coef)) - start
                if unit is 'ms':
                    print(f"{helper.__name__} - {helper.calls} - {end_ if end_ > 0 else 0} ms")
                else :
                    print(f"{helper.__name__} - {helper.calls} - {end_ if end_ > 0 else 0} s")
        helper.calls = 0
        helper.__name__ = func.__name__
        return helper

    return decorator

@logging(unit='ms')
def calculate_force(a_object, *b_object):
    force = Force(0, 0)
    for i in b_object:
    
        distance = pow(pow(i.x - a_object.x, 2) + pow(i.y - a_object.y, 2), 1/2)

        F_ij = G*a_object.mass*i.mass/pow(distance, 2)

        F_x = abs(F_ij)*(i.x - a_object.x)/distance
        F_y = abs(F_ij)*(i.y - a_object.y)/distance

        force = Force(force.fx + F_x, force.fy + F_y)
   
    return force

@logging(unit='ms')
def update_space_object(space_object, force, timestep):

    acceleration_x = force.fx/space_object.mass
    acceleration_y = force.fy/space_object.mass

    speed_change_x = acceleration_x * timestep
    speed_change_y = acceleration_y * timestep

    speed_new_x = space_object.vx + speed_change_x
    speed_new_y = space_object.vy + speed_change_y

    x = space_object.x + speed_new_x * timestep
    y = space_object.y + speed_new_y * timestep
    new_space_object = SpaceObject(space_object.name, space_object.mass, x, y, speed_new_x, speed_new_y, space_object.color)
    return new_space_object

@logging(unit='ms')
def update_motion(timestep, objects):

    planets = list()
    for i in objects:
        force = Force(0, 0)
        for j in objects:
            if i != j :
                tmp_force = calculate_force(i, j)
                force = Force(force.fx + tmp_force.fx, force.fy + tmp_force.fy)
        planets.append(update_space_object(i, force, timestep))

    return planets
    
    
@logging()
def simulate_motion(timestep, num, *objects):
    for i in range(num):
        planets = {}
        objects = update_motion(timestep, objects)
        for j in objects:
            planets[j.name] = (j.x, j.y)
        yield planets