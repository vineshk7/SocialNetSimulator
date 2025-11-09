#ifndef POST_HPP
#define POST_HPP

#include <string>
using namespace std;   
/**
 * @struct Post
 * @brief Represents a single post made by a user.
 * It stores the content and a unique ID to determine creation time.
 */
struct Post {
    string content;
    int postID;

    Post(string content = "", int id = 0) : content(content), postID(id) {}

    // Operator overloads for comparison in the AVL Tree
    bool operator<(const Post& other) const {
        return postID < other.postID;
    }
    bool operator>(const Post& other) const {
        return postID > other.postID;
    }
    bool operator==(const Post& other) const {
        return postID == other.postID;
    }
};

#endif 