#include <gtest/gtest.h>
#include "pattern/observer.h"

TEST(EventTest, CanSubscribeAndRaise)
{
    BOSSCorp::Pattern::Observer<bool> event;

    bool raised = false;
    event.subscribe([&](bool b) {
        raised = true;
    });

    event.raise(false);

    ASSERT_TRUE(raised);
}

TEST(EventTest, CanRaiseMultiple)
{
   BOSSCorp::Pattern::Observer<bool> event;

    bool raised1 = false;
    bool raised2 = false;
    event.subscribe([&](bool b) {
        raised1 = true;
    });

    event.subscribe([&](bool b) {
        raised2 = true;
    });

    event.raise(false);

    ASSERT_TRUE(raised1);
    ASSERT_TRUE(raised2);
}

TEST(EventTest, CanSubscribeMemberFunction)
{
    struct TestType{
        bool success;
        void member(bool x) { success = true; }

        explicit TestType(BOSSCorp::Pattern::Observer<bool>& event) {
            event.subscribe([this](bool b) { member(b); });
        }
    };

    BOSSCorp::Pattern::Observer<bool> event;
    
    TestType t(event);
    event.raise(false);   
 
    ASSERT_TRUE(t.success);
}