#include "vending_machine.h"
#include "ctype.h"
#include "test.c"

#define TESTING 1

#if TESTING
int main(){

vending_machine gumball;
initialize_machine(&gumball);

/* Balance is 0 */
testBool(FALSE, dispense_item('Y', &gumball), "Fail to Dispense Yellow with 0 Balance");
testBool(FALSE, dispense_item('R', &gumball), "Fail to Dispense Red with 0 Balance");

/* Setup balance to be >=10 cents */
set_gumball_balance(10, &gumball);
testBool(TRUE, dispense_item('Y', &gumball), "Able to dispense Yellow with Balance >=10 cents test");
set_gumball_balance(100, &gumball);
testBool(TRUE, dispense_item('Y', &gumball), "Able to dispense Yellow with Balance >=10 cents test");

/* Setup balance to be <10 cents */
set_gumball_balance(9, &gumball);
testBool(FALSE, dispense_item('Y', &gumball), "Not able to dispense Yellow with Balance <10 cents test");
set_gumball_balance(1, &gumball);
testBool(FALSE, dispense_item('Y', &gumball), "Not able to dispense Yellow with Balance <10 cents test");

/* Setup balance to be >=5 cents */
set_gumball_balance(5, &gumball);
testBool(TRUE, dispense_item('R', &gumball), "Able to dispense Red with Balance >=5 cents test");
set_gumball_balance(100, &gumball);
testBool(TRUE, dispense_item('R', &gumball), "Able to dispense Red with Balance >=5 cents test");

/* Setup balance to be <5 cents */
set_gumball_balance(4, &gumball);
testBool(FALSE, dispense_item('R', &gumball), "Not able to dispense Red with Balance <5 cents test");

set_gumball_balance(1, &gumball);
testBool(FALSE, dispense_item('R', &gumball), "Not able to dispense Red with Balance <5 cents test");
set_gumball_balance(0, &gumball);


insert_coin('D', &gumball);
insert_coin('N', &gumball);
insert_coin('Q', &gumball);
testBool(40, return_change(&gumball), "Correct change dispensed");
set_gumball_balance(0, &gumball);

insert_coin('D', &gumball);
insert_coin('D', &gumball);
insert_coin('D', &gumball);
testBool(40, return_change(&gumball), "Correct change dispensed");
set_gumball_balance(0, &gumball);

insert_coin('P', &gumball);
testBool(1, return_invalid_currency(&gumball), "Correct pennies dispensed");
set_gumball_penny(0, &gumball);

insert_coin('P', &gumball);
insert_coin('P', &gumball);
insert_coin('P', &gumball);
testBool(6, return_invalid_currency(&gumball), "Correct pennies dispensed");
set_gumball_penny(0, &gumball);
}
#else

static uint8_t input_is_coin(char input);
static uint8_t input_is_color(char input);


int main(void){
    uint8_t status = TRUE;
    char input;
    vending_machine gumball;

    initialize_machine(&gumball);

    while(status){
        print_interface(&gumball);
        scanf(" %c", &input);
        input = toupper(input);
        if( input_is_coin(input) ){
            insert_coin(input, &gumball);
        }
        else if( input_is_color(input) ){
            if( !dispense_item( input, &gumball) ){
                printf("\nNot enough credits. Please try again.");
            }
        }
        else if( input == 'X'){
            return_change(&gumball);
            status = FALSE;
        }
        else{
            printf("\nInvalid input. Try again.\n");
        }
    }
    return 0;
}

uint8_t input_is_coin(char input){
    if( (input == 'N') | (input == 'D') | (input == 'Q') | (input == 'P')){
        return TRUE;
    }
    return FALSE;
}
uint8_t input_is_color(char input){
    if( (input == 'Y') | (input == 'R') ){
        return TRUE;
    }
    return FALSE;
}
#endif