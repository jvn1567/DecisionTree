#include <string>

class MagicParent {
    private:
        virtual std::string method1() = 0;
    public:
        std::string method2() {
            return method1();
        }
};

class MagicChild : public MagicParent {
    private:
        std::string method1() {
            return "It's magic!\n";
        }
};