#ifndef SOCIALNET_HPP
#define SOCIALNET_HPP

#include <string>
#include <unordered_map>
#include <vector>
#include <queue>
#include <set>
#include <map>
#include <sstream>
#include "User.hpp"


class SocialNet {
private:
    std::unordered_map<std::string, User*> userMap;
    
    // Global counter for post IDs to ensure chronological order
    int globalPostID;

    /**
     * @brief Gets a user pointer from the map.
     * @param username Normalized username.
     * @return Pointer to the User object, or nullptr if not found.
     */
    User* getUser(const std::string& username);

public:
    /**
     * @brief Constructor: Initializes the network.
     */
    SocialNet();

    /**
     * @brief Destructor: Cleans up all dynamically allocated User objects.
     */
    ~SocialNet();

    /**
     * @brief Processes a single command line from stdin.
     * @param line The full command line.
     */
    void processCommand(const std::string& line);

    // --- Command Implementations ---

    /**
     * @brief Adds a new user to the network.
     * @param username The username to add.
     */
    void addUser(const std::string& username);

    /**
     * @brief Adds a bidirectional friendship.
     * @param user1 First user.
     * @param user2 Second user.
     */
    void addFriend(const std::string& user1, const std::string& user2);

    /**
     * @brief Lists all friends of a user, alphabetically.
     * @param username The user whose friends to list.
     */
    void listFriends(const std::string& username);

    /**
     * @brief Calculates degrees of separation using BFS.
     * @param user1 Starting user.
     * @param user2 Ending user.
     */
    void degreesOfSeparation(const std::string& user1, const std::string& user2);

    /**
     * @brief Suggests N friends (friends of friends).
     * @param username The user to suggest friends for.
     * @param N The maximum number of suggestions.
     */
    void suggestFriends(const std::string& username, int N);

    /**
     * @brief Adds a post for a user.
     * @param username The user who is posting.
     * @param content The content of the post.
     */
    void addPost(const std::string& username, const std::string& content);

    /**
     * @brief Outputs the N most recent posts for a user.
     * @param username The user whose posts to show.
     * @param N The number of posts to show (-1 for all).
     */
    void outputPosts(const std::string& username, int N);
};

#endif 
