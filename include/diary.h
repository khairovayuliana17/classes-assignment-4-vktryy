
// declare Diary class here

#include <string>
#include <iostream>

class Diary {
  private:
    // your code here

  public:
    Diary(const std::string& initialPassword);
    ~Diary();

    bool unlock(const std::string& inputPassword);
    void write(const std::string& text);
    void lock();
    std::string read();
};
