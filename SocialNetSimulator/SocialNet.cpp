#include "SocialNet.hpp"
#include "utils.hpp"
#include <iostream>
#include <algorithm>
#include <unordered_set>
#include <map> // For suggestFriends
#include <queue> // For degreesOfSeparation

SocialNet::SocialNet() : globalPostID(0) {}

SocialNet::~SocialNet() {
    for (auto& pair : userMap) {
       delete pair.second;
    }
}

User* SocialNet::getUser(const std::string& username) {
    auto it = userMap.find(username);
    if (it == userMap.end()) {
       return nullptr;
    }
    return it->second;
}


// --- Command Processing ---

void SocialNet::processCommand(const std::string& line) {
    std::stringstream ss(line);
    std::string command;
    ss >> command;

    std::string normCommand = normalize(command);

    if (normCommand == "add_user") {
        std::string username;
        ss >> username;
        if (!username.empty())
            addUser(username);
    } 
    else if (normCommand == "add_friend") {
        std::string user1, user2;
        ss >> user1 >> user2;
        if (!user1.empty() && !user2.empty())
            addFriend(user1, user2);
    }
    else if (normCommand == "list_friends") {
        std::string username;
        ss >> username;
        if (!username.empty())
            listFriends(username);
    }
    else if (normCommand == "degrees_of_separation") {
        std::string user1, user2;
        ss >> user1 >> user2;
        if (!user1.empty() && !user2.empty())
            degreesOfSeparation(user1, user2);
    }
    else if (normCommand == "suggest_friends") {
        std::string username;
        int N;
        ss >> username >> N;
        if (!username.empty()) 
            suggestFriends(username, N);
    }
    else if (normCommand == "add_post") {
        std::string username;
        std::string content;
        ss >> username;
        std::getline(ss, content);
        if (!username.empty())
            addPost(username, content);
    }
    else if (normCommand == "output_posts") {
        std::string username;
        int N;
        ss >> username >> N;
        if (!username.empty())
            outputPosts(username, N);
    }
}


// --- Command Implementations ---

void SocialNet::addUser(const std::string& username) {
    std::string normUser = normalize(username);
    if (userMap.find(normUser) != userMap.end()) {
        std::cout << "User already exists." << std::endl;
        return;
    }
    User* newUser = new User(normUser);
    userMap[normUser] = newUser;
}

void SocialNet::addFriend(const std::string& user1, const std::string& user2) {
    std::string normUser1 = normalize(user1);
    std::string normUser2 = normalize(user2);
    User* u1 = getUser(normUser1);
    User* u2 = getUser(normUser2);
    if (!u1 || !u2) { 
        std::cout << "User not found." << std::endl;
        return; 
    }
    if (u1 == u2) {
        std::cout << "Cannot add self as friend." << std::endl;
        return; 
    }
    for (User* friendP : u1->friends) {
        if (friendP == u2) {
            std::cout << "Already friends." << std::endl;
            return; 
        }
    }
    u1->addFriend(u2);
    u2->addFriend(u1);
}

void SocialNet::listFriends(const std::string& username) {
    std::string normUser = normalize(username);
    User* user = getUser(normUser);
    if (!user) {
        return;
    }
    if (user->friends.empty()) {
        cout << "No friends found." << endl;
        return;
    }
    // 2. Extract friend usernames
    std::vector<std::string> friendNames;
    for (User* friendPtr : user->friends) {
        friendNames.push_back(friendPtr->username);
    }
    // 3. Sort friendNames alphabetically
    std::sort(friendNames.begin(), friendNames.end());
    // 4. Print each name on a new line
    for (const std::string& name : friendNames) {
        std::cout << name << std::endl;
    }
}

void SocialNet::degreesOfSeparation(const std::string& user1, const std::string& user2) {
    std::string normUser1 = normalize(user1);
    std::string normUser2 = normalize(user2);
    User* u1 = getUser(normUser1);
    User* u2 = getUser(normUser2);
    if (!u1 || !u2) {
        std::cout << "User not found." << std::endl;
        std::cout << -1 << std::endl;
        return;
    }
    if (u1 == u2) {
        std::cout << "Usernames are the same." << std::endl;
        std::cout << 0 << std::endl;
        return;
    }
    std::queue<User*> q;
    std::unordered_map<User*, int> distance;
    q.push(u1);
    distance[u1] = 0;
    bool check = false;
    while(!q.empty()) {
        User* current = q.front();
        q.pop();
        if (current == u2) {
            check = true;
            break;
        }
        for (User* neighbor : current->friends) {
            if (distance.find(neighbor) == distance.end()) { 
                distance[neighbor] = distance[current] + 1;
                q.push(neighbor);
            }
        }
    }
    if (check) {
        std::cout << distance[u2] << std::endl;
    } else {
        std::cout << -1 << std::endl;
    }
}

void SocialNet::suggestFriends(const std::string& username, int N) {
    std::string normUser = normalize(username);
    if (N <= 0) {
        return;
    }
    User* user = getUser(normUser);
    if (!user) {
        std:: cout << "User not found." << std::endl;
        return;
    }
    std::unordered_set<User*> directFriends;
    for(User* friendPtr : user->friends) {
        directFriends.insert(friendPtr);
    }
    std::map<User*, int> suggestions;
    for(User* friendPtr : user->friends) {
        for(User* friendOfFriend : friendPtr->friends) {
            if (friendOfFriend != user && directFriends.find(friendOfFriend) == directFriends.end()) {
                suggestions[friendOfFriend]++; 
            }
        }
    }
    std::vector<std::pair<User*, int>> sortedSuggestions(suggestions.begin(), suggestions.end());
    std::sort(sortedSuggestions.begin(), sortedSuggestions.end(),
              [](const std::pair<User*, int>& a, const std::pair<User*, int>& b) {
                  if (a.second != b.second) {
                      return a.second > b.second;
                  }
                  return a.first->username < b.first->username;
              });
    int size = sortedSuggestions.size();
    if (N > size) {
        for (int i = 0; i < size; i++) {
            std::cout << sortedSuggestions[i].first->username << std::endl;
        }
    } else {
        for (int i = 0; i < N; i++) {
            std::cout << sortedSuggestions[i].first->username << std::endl;
        }
    }
}

void SocialNet::addPost(const std::string& username, const std::string& content) {
    std::string normUser = normalize(username);
    User* user = getUser(normUser);
    if (!user) {
        std::cout << "User not found." << std::endl;
        return;
    }
    if (user) {
        std::string trimmedContent = trim(content);
        std::string normalizedContent = normalize(trimmedContent);
        Post newPost(normalizedContent, globalPostID++);
        user->userPosts.insert(newPost);
    }
}

void SocialNet::outputPosts(const std::string& username, int N) {
    std::string normUser = normalize(username);
    User* user = getUser(normUser);
    if (!user) {
        std::cout << "User not found." << std::endl;
        return;
    }
    if (user) {
       user->userPosts.outputPosts(N);
    }
}