#include "vending_machine.h"


/* Test Cases:
 *
 *  Zero balance test:
 *  - Red 5cents
 *  - Yellow 10cents
 * 
 *  Red lever states:
 *  - balance is >=5cents
 *  - balance is <5cents
 * 
 *  Yellow lever states:
 *  - balance is >=10 cents
 *  - balance is <10cents
 * 
 *  Change tests:
 *  - Balance is 0 no invalid currency, Return 0 change
 *  - Balance is 0 with invalid currency, return 0 change
 *  - 
 * 
 */
 
void testBool(uint8_t expected, uint8_t actual, const char* testName){
    if(expected == actual){
        printf("\nPASSED %s : ", testName);
    } else {
        printf("\nFAILED %s , expected: %u actual: %u ", testName, expected, actual);
    }
} 

//void testInit(--- expected, --- actual initialize_machine( --- )) {
//  if(expected == actual){
//      printf("\n%s PASSED: ", testName);
//  } else {
//      printf("\n%s FAILED, expected: %d actual: %d ", testName, expected, actual);
//  }
//}

// void testInsert(char* expected, char* actual, const char* testName){
//     if(expected == actual){
//         printf("\n%s PASSED: ", testName);
//     } else {
//         printf("\n%s FAILED, expected: %s actual: %s ", testName, expected, actual);
//     }
// }

// testing the amount of change right, but what about penny objects?
// void testReturnChange(int expected, int actual, const char* testName){
//     if(expected == actual){
//         printf("\n%s PASSED: ", testName);
//     } else {
//         printf("\n%s FAILED, expected: %s actual: %s ", testName, expected, actual);
//     }
// }


// how to test voids? maybe idividualized test or unique test per 
// [~]testVoid(----, initialize_machine( --- ))
// [0]testVoid(----, insert_coin("Q", &gumball))
// [0]testVoid(----, return_change(vending_machine *machine))
// [?]testVoid(----, print_interface(vending_machine *machine))