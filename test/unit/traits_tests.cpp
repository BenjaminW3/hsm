#include "hsm/hsm.h"

#include <gtest/gtest.h>

#include <boost/hana.hpp>

using namespace ::testing;

class TraitsTests : public Test {
};

class S1 {
};
class S2 {
};

TEST_F(TraitsTests, should_recognize_exit_state)
{
    auto exit = hsm::Exit(S1 {}, S2 {});

    boost::hana::if_(
        hsm::is_exit_state(exit),
        [](auto exit) { ASSERT_TRUE(true); },
        [&](auto) { ASSERT_TRUE(false); })(exit);
}

TEST_F(TraitsTests, should_call_callable)
{
    namespace bh = boost::hana;

    auto called = false;
    auto callable = [&called](int){called = true;};
    auto arg = 1;
    auto args = bh::make_tuple(arg);

    bh::if_(hsm::is_callable(callable, args),
                 [arg](auto callable){return callable(arg);},
                 [](auto callable){return 1;})(callable);

    ASSERT_TRUE(called);                 
}

TEST_F(TraitsTests, should_not_call_callable)
{
    namespace bh = boost::hana;

    struct Arg {
    };

    auto callable = [](Arg arg){return 42; };
    auto not_callable = [] (){throw 42; };
    Arg arg;
    auto args = bh::make_tuple(arg);

    bh::if_(hsm::is_callable(callable, args),
                    [arg](auto callable){ return callable(arg);},
                    [](auto callable){ return 1; })(callable);                    
    bh::if_(hsm::is_callable(not_callable, args),
                    [arg](auto callable){ return callable(arg);},
                    [](auto callable){ return 1; })(not_callable);
}