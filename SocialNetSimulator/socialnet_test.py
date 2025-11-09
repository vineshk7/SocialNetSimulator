import random

USER_NAMES = [
    "alice", "bob", "charlie", "david", "eve", "frank", "grace", "heidi", 
    "ivan", "judy", "ken", "laura", "mallory", "nancy", "oscar", "peggy", 
    "quinn", "roger", "susan", "trent", "ursula", "victor", "wendy", 
    "xavier", "yara", "zane"
]

NUM_USERS = len(USER_NAMES)
NUM_FRIENDSHIPS = 75
NUM_POSTS = 150
NUM_QUERIES = 200

POST_TEMPLATES = [
    "just joined socialnet!",
    "thinking about {0}",
    "had a great day today",
    "I can't believe {0} and {1} are friends",
    "feeling happy",
    "a bit tired today",
    "my first post!",
    "hello {0}"
]

def get_users(n=1):
    return random.sample(USER_NAMES, n)

print(f"--- Generating 'input.txt' with {NUM_USERS} users... ---")

with open("input.txt", "w") as f:
    
    def write_command(cmd):
        print(f"  {cmd}")
        f.write(cmd + "\n")

    print("\n[Stage 1] Adding Users...")
    for user in USER_NAMES:
        write_command(f"ADD_USER {user}")
    
    write_command(f"ADD_USER alice") # duplicate check

    print("\n[Stage 2] Adding Friendships...")
    for _ in range(NUM_FRIENDSHIPS):
        user1, user2 = get_users(2)
        write_command(f"ADD_FRIEND {user1} {user2}")
    
    write_command(f"ADD_FRIEND bob bob")  # edge case
    write_command(f"ADD_FRIEND alice bob")  # edge case


    print("\n[Stage 3] Adding Posts...")
    for _ in range(NUM_POSTS):
        user = get_users(1)[0]
        template = random.choice(POST_TEMPLATES)
        post_content = template.format(*get_users(2))
        write_command(f"ADD_POST {user} {post_content}")
    
    write_command(f"ADD_POST eve")  # correctness check
    write_command(f"ADD_POST frank    ") # correctness check


    print("\n[Stage 4] Running Queries...")
    for _ in range(NUM_QUERIES):
        user1, user2 = get_users(2)
        rand_n = random.randint(1, 5)
        rand_all = random.choice([rand_n, -1, 0])

        command_type = random.randint(0, 3)

        if command_type == 0:
            write_command(f"LIST_FRIENDS {user1}")
        elif command_type == 1:
            write_command(f"DEGREES_OF_SEPARATION {user1} {user2}")
        elif command_type == 2:
            write_command(f"SUGGEST_FRIENDS {user1} {rand_all}")
        elif command_type == 3:
            write_command(f"OUTPUT_POSTS {user1} {rand_all}")

## Get-Content input.txt | ./SocialNet.exe > output.txt