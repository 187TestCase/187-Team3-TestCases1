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

/* Innsert coin max edge case. Vending machine does not accept more than 255 of a coin */
set_gumball_nickel( 255, &gumball);
testBool(FALSE, insert_coin( 'N', &gumball), "Nickel count > 255 not allowed");
set_gumball_dime( 255, &gumball);
testBool(FALSE, insert_coin( 'D', &gumball), "Dime count > 255 not allowed");
set_gumball_quarter( 255, &gumball);
testBool(FALSE, insert_coin( 'Q', &gumball), "Quarter count > 255 not allowed");

reset_machine(&gumball);

insert_coin('D', &gumball);
insert_coin('N', &gumball);
insert_coin('Q', &gumball);
testBool(40, return_change(&gumball), "Correct change dispensed");
set_gumball_balance(0, &gumball);

insert_coin('D', &gumball);
insert_coin('D', &gumball);
insert_coin('D', &gumball);
testBool(30, return_change(&gumball), "Correct change dispensed");
set_gumball_balance(0, &gumball);

insert_coin('P', &gumball);
testBool(1, return_invalid_currency(&gumball), "Correct pennies dispensed");

insert_coin('P', &gumball);
insert_coin('P', &gumball);
insert_coin('P', &gumball);
testBool(3, return_invalid_currency(&gumball), "Correct pennies dispensed");
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
            /* User inserts a coin */
            if( !insert_coin(input, &gumball) ){
                printf("\nMax count of type '%c' inserted.", input);
            }
        }
        else if( input_is_color(input) ){
            /* User pulls a lever */
            if( dispense_item( input, &gumball) ){
                printf("\n%c gumball dispensed.\n", input);
            }
            else{
                printf("\nNot enough credits to dispense '%c' gumball. \nPlease try again.", input);
            }
        }
        else if( input == 'X'){
            /* User exits the program "Leaves the vending machine" */
            printf("\nChange Returned: %u cents", return_change(&gumball));
            printf("\nQuarters: %u \nDimes: %u \nNickels: %u", get_quarter_count(&gumball), get_dime_count(&gumball), get_nickel_count(&gumball));
            printf("\n\nInvalid currency returned:\nPennies: %u\n\n", return_invalid_currency(&gumball));
            return_change(&gumball);
            status = FALSE;
        }
        else{
            /* User inputs an invalid option */
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