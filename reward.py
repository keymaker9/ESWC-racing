def reward_function(params):
    '''
    Enhanced reward function to further optimize track performance and obstacle avoidance.
    '''
    # Read input parameters
    all_wheels_on_track = params['all_wheels_on_track']
    distance_from_center = params['distance_from_center']
    track_width = params['track_width']
    objects_distance = params['objects_distance']
    _, next_object_index = params['closest_objects']
    objects_left_of_center = params['objects_left_of_center']
    is_left_of_center = params['is_left_of_center']
    steering_angle = params['steering_angle']
    speed = params['speed']

    # Initialize reward
    reward = 1e-3

    # Reward for staying in the lane
    reward_lane = 1.0 if all_wheels_on_track and (0.5 * track_width - distance_from_center) >= 0.05 else 1e-3
    if distance_from_center < 0.35 * track_width:
        reward_lane += 1.0  # Bonus for being close to the center
    elif distance_from_center < 0.5 * track_width:
        reward_lane += 3.33 * (0.5 * track_width - distance_from_center)
    else:
        reward_lane = 1e-3  # Penalize heavily for being too far from the center

    # Reward for avoiding obstacles
    reward_avoid = 1.0
    distance_closest_object = objects_distance[next_object_index]
    is_same_lane = objects_left_of_center[next_object_index] == is_left_of_center

    if is_same_lane:
        if distance_closest_object < 0.15:
            reward_avoid = 1e-3  # Likely crash
        elif 0.15 <= distance_closest_object < 0.3:
            reward_avoid *= (distance_closest_object - 0.25) * 4 + 1e-3
        elif 0.3 <= distance_closest_object < 0.8:
            reward_avoid *= 0.5  # Moderate penalty
        else:
            reward_avoid *= 1.0  # Safe distance

    # Enhanced speed adjustment based on steering angle
    reward_speed = 1.0
    if abs(steering_angle) < 5:  # Straight driving
        if speed > 3.0:
            reward_speed += 3.0
        elif speed > 2.0:
            reward_speed += 2.0
    elif abs(steering_angle) < 15:  # Gentle turns
        if speed > 2.5:
            reward_speed += 1.0
        elif speed > 2.0:
            reward_speed += 0.5
    elif abs(steering_angle) > 15:  # Sharp turns
        if speed < 1.8:
            reward_speed += 1.0
        elif speed < 2.2:
            reward_speed += 0.5

    # Final reward calculation
    reward = (2.0 * reward_lane) + (3.0 * reward_avoid) + (2.0 * reward_speed)

    return reward
