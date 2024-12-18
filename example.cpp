#include "cppdataloader.hpp"

#include <iostream>

class User {
  public:
    User(long _id): id(_id) {}
    long id;
};

class UserBatchLoader : public BatchLoader<long, User> {
  public:
    std::vector<User> load(std::vector<long> userIds) const override {
      auto result = std::vector<User>();
      // Make a DB call here or something and pass in userIds to SELECT and return
      for (auto userId : userIds)
        result.push_back(User(userId));
      return result;
    }
};

int main(int argc, char *argv[]) {
  UserBatchLoader userBatchLoader = UserBatchLoader();
  DataLoader<long, User> userLoader = DataLoader(userBatchLoader);

  std::future<User> load1 = userLoader.load(1);
  std::future<User> load2 = userLoader.load(2);

  userLoader.dispatch();

  std::cout << load1.get().id << load2.get().id << std::endl;
}
