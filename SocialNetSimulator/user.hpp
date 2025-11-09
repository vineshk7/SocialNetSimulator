#ifndef USER_HPP
#define USER_HPP

#include <string>
#include <vector>
#include "AVLTree.hpp"
using namespace std;

/**
 * @class User
 * @brief Represents a user in the social network.
 * This is a vertex in the graph. It holds the user's posts and a list of friends.
 */
class User {
public:
    string username;     // Normalized (lowercase) username
    vector<User*> friends; // Adjacency list
    AVLTree userPosts;      // Root of this user's post tree

    User(string name) : username(name) {}

    void addFriend(User* friendUser) {
        friends.push_back(friendUser);
    }
};

#endif