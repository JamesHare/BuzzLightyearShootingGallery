#include <target.h>
#include <unity.h>


void test_getServoPinNumber(void) {
    Target testTarget(1, A1, 2);
    TEST_ASSERT_EQUAL(1, testTarget.getServoPinNumber);
}

void test_getPhotoresistorPinNumber(void) {
    Target testTarget(1, A1, 2);
    TEST_ASSERT_EQUAL(A1, testTarget.getPhotoresistorPinNumber);
}

void test_getLEDPinNumber(void) {
    Target testTarget(1, A1, 2);
    TEST_ASSERT_EQUAL(2, testTarget.getLedPinNumber);
}

void process() {
    UNITY_BEGIN();
    RUN_TEST(test_getServoPinNumber);
    RUN_TEST(test_getPhotoresistorPinNumber);
    RUN_TEST(test_getLEDPinNumber);
    UNITY_END();
}

int main(int argc, char **argv) {
    process();
    return 0;
}