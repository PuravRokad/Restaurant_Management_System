#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int i_count = 0, w_count = 0, m_count = 0;
struct w{
char name[20];
int member, sr;
struct w *next, *prev;
} *w_h, *w_c, *w_t;
struct menu{
struct menu *next, *prev;
int sr;
char item[100];
float price;
} *m_h, *m_c, *m_t;

struct customer{
struct customer *next, *prev;
struct order{
    struct order *next, *prev;
    char o_i[100];
    int qty;
    float o_price;
} *o_h, *o_c, *o_t;
char name[20];
char no[15];
float total;
} *c_h, *c_c, *c_t;

void red () {
  printf("\033[1;31m");
}

void yellow () {
  printf("\033[1;33m");
}

void black (){
  printf("\033[0;30m");
}

void green (){
  printf("\033[0;32m");
}

void blue (){
  printf("\033[0;34m");
}

void purple (){
  printf("\033[0;35m");
}

void cyan () {
  printf("\033[0;36m");
}

void reset () {
  printf("\033[0m");
}

void display(){
    int buffer = 18;
    struct menu *print;
    print = m_h;
    blue();
    printf("<---------------------------------------------------- ");
    red();
    printf("Menu");
    blue();
    printf(" ---------------------------------------------------->\n");
    reset();
    printf("----------------------------------------------------------------------------------------------------------------\n");
    cyan();
    printf("Sr.No.\t\t\t\t\tItem\t\t\t\t\t\t\tPrice(in Rs.)\n");
    reset();
    printf("----------------------------------------------------------------------------------------------------------------\n");
    while(1){
        //if(print == m_h) break;
        int space = buffer - strlen(print -> item);
        printf("%d\t\t\t\t\t%s",print -> sr, print -> item);
        for(int i = 0; i < space; ++i){
            printf(" ");
        }
        green();
        printf("\t\t\t\t\t%.2f\n", print -> price);
        reset();
        print = print -> next;
       if(print == m_h) break;
    }
}
void o_item(){
    int choice;
    rechoice:
    printf("\nEnter the Sr.No. of Item you want to order: ");
    green();
    scanf("%d", &choice);
    struct menu *tm;
    tm = m_h;
    int check = 1;
    while(tm != NULL){
        if(tm -> sr == choice){
            int q;
            reset();
            printf("Enter the Quantity: ");
            green();
            scanf("%d", &q);
            reset();
            struct order *temp;
            temp = c_c -> o_h;
            int check1 = 1;
            while(temp != NULL){
                if(strcmp(temp -> o_i, tm -> item) == 0){
                    temp -> qty += q;
                    c_c -> total += (q * tm -> price);
                    check1 = 0;
                    break;
                }
                temp = temp -> next;
            }
            if(check1){
            c_c -> o_c = (struct order*)malloc(sizeof(struct order));
            if(c_c -> o_h == NULL){
                c_c -> o_h = c_c -> o_c;
                c_c -> o_t = c_c -> o_c;
                strcpy(c_c -> o_c -> o_i, tm -> item);
                c_c -> o_c -> qty = q;
                c_c -> o_c -> o_price = tm -> price;
                c_c -> total += (q * tm -> price);
            }
            else{
                c_c -> o_t -> next = c_c -> o_c;
                c_c -> o_c -> prev = c_c -> o_t;
                strcpy(c_c -> o_c -> o_i, tm -> item);
                c_c -> o_c -> qty = q;
                c_c -> o_c -> o_price = tm -> price;
                c_c -> o_t = c_c -> o_c;
                c_c -> total += (q * tm -> price);
            }
            }
            printf("Added item total = \033[0;35m%.2f\n", q * tm -> price);
            reset();
            printf("Total Amount till now = \033[0;32m%.2f", c_c -> total);
            printf("\nOrder Added!\n");
            reset();
            check = 0;
            i_count++;
            break;
        }
        tm = tm -> next;
        if(tm == m_h){
            break;
        }
    }
    if(check){
        red();
        printf("Enter a Valid Sr.No.!!\n");
        reset();
        goto rechoice;
    }
}
void display_wait(){
    struct w *p;
    p = w_h;
    if(p == NULL){
        green();
        printf("\nTheir is No Waiting!\n");
        reset();
    }
    else{
    int buffer = 20;
    printf("\n\033[0;34m<------------------------------------------------ \033[1;31mWaiting List\033[0;34m ------------------------------------------------>\033[0m\n\n");
    printf("----------------------------------------------------------------------------------------------------------------\n");
    printf("Sr.No.\t\t\t\t\tName\t\t\t\t\t\t\tMembers\n");
    printf("----------------------------------------------------------------------------------------------------------------\n");
    while(1){
        int space = buffer - strlen(p ->name);
        printf("%d\t\t\t\t\t%s",p -> sr, p -> name);
        for(int i = 0; i < space; ++i){
            printf(" ");
        }
        printf("\t\t\t\t\t%d\n", p -> member);
        p = p -> next;
        if(p == w_h) break;
    }
    }
}
void display_invoice(struct customer *c_c){
    struct order *tem;
    tem = c_c -> o_h;
    if(tem == NULL){
        yellow();
        printf("\nNO ORDER IS GIVEN!!\n");
        reset();
        return;
    }
    red();
 printf("\t\t\t MADOVER GRILLS Restaurant \t\t\t\t\n");
 reset();
 printf("\t\t\t---------------------------\t\t\t\t\n");
 time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    printf("\033[0;34mDate: \033[0;37m%d-%02d-%02d \033[0m\n",tm.tm_mday, tm.tm_mon + 1,tm.tm_year + 1900);
    printf("\033[0;34mInvoice to: \033[0;37m%s\033[0m\n", c_c -> name);
    printf("\033[0;34mMobile No.: \033[0;37m%s\033[0m\n", c_c -> no);
    printf("-------------------------------------------------------------------------\n");
    printf("Items\t\t\t\tQty.\t\t\t\t Price\n");
    printf("-------------------------------------------------------------------------\n\n");
    while(tem != NULL){
        int space = 20 - strlen(tem -> o_i);
        printf("%s", tem -> o_i);
        for(int i = 0; i < space; ++i){
            printf(" ");
        }
        printf("\t\t%d\t\t\t\t %.2f\n", tem -> qty, tem -> qty * tem -> o_price);
        tem = tem -> next;
    }
    printf("\n-------------------------------------------------------------------------\n");
    printf("Subtotal\t\t\t\t\t\t\t %.2f\n", c_c -> total);
    float discount = ((c_c -> total)*10)/100;
    printf("Discount@10%%\t\t\t\t\t\t\t %.2f\n",discount);
    printf("        \t\t\t\t\t\t     ------------\n");
    float net = c_c -> total - discount;
    printf("Net Total\t\t\t\t\t\t\t %.2f\n",net);
    printf("CGST@9%%\t\t\t\t\t\t\t\t %.2f\n",(net*9)/100);
    printf("SGST@9%%\t\t\t\t\t\t\t\t %.2f\n",(net*9)/100);
    printf("-------------------------------------------------------------------------\n");
    printf("Grand Total\t\t\t\t\t\t\t\033[0;32m %.2f\n",net + (net*9)/50);
    reset();
    printf("-------------------------------------------------------------------------\n");
}
void sort(){
    struct customer *t, *t1;
    t = c_h;
    while(t != NULL){
        t1 = t -> next;
        while(t1 != NULL){
            if(t -> total < t1 -> total){
                char n[20];
                strcpy(n,t1 -> name);
                strcpy(t1 -> name, t -> name);
                strcpy(t -> name, n);
                int tt = t1 -> total;
                t1 -> total = t -> total;
                t -> total = tt;
                struct order *t2;
                t2 = t -> o_h;
                t -> o_h = t1 -> o_h;
                t1 -> o_h = t2;
            }
            t1 = t1 -> next;
        }
        t = t -> next;
    }
}
void showInvoice(){
    sort();
    float total = 0;
struct customer *temp;
temp = c_h;
printf("\n<----------------------------------- List of all Invoices ----------------------------------->\n\n");
while(temp != NULL){
    struct order *tem;
    tem = temp -> o_h;
    if(tem == NULL){
        temp = temp -> next;
        continue;
    }
    red();
    printf("\t\t\t MADOVER GRILLS Restaurant \t\t\t\t\n");
    reset();
    printf("\t\t\t---------------------------\t\t\t\t\n");
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    printf("\033[0;34mDate: \033[0;37m%d-%02d-%02d \033[0m\n",tm.tm_mday, tm.tm_mon + 1,tm.tm_year + 1900);
    printf("\033[0;34mInvoice to: \033[0;37m%s\033[0m\n", temp -> name);
    printf("\033[0;34mMobile No.: \033[0;37m%s\033[0m\n", temp -> no);
    printf("-------------------------------------------------------------------------\n");
    printf("Items\t\t\t\tQty.\t\t\t\t Price\n");
    printf("-------------------------------------------------------------------------\n\n");
    while(tem != NULL){
        int space = 20 - strlen(tem -> o_i);
        printf("%s", tem -> o_i);
        for(int i = 0; i < space; ++i){
            printf(" ");
        }
        printf("\t\t%d\t\t\t\t %.2f\n", tem -> qty, tem -> qty * tem -> o_price);
        tem = tem -> next;
    }
    printf("\n-------------------------------------------------------------------------\n");
    printf("Subtotal\t\t\t\t\t\t\t %.2f\n", temp -> total);
    float discount = ((temp -> total)*10)/100;
    printf("Discount@10%%\t\t\t\t\t\t\t %.2f\n",discount);
    printf("        \t\t\t\t\t\t     ------------\n");
    float net = temp -> total - discount;
    printf("Net Total\t\t\t\t\t\t\t %.2f\n",net);
    printf("CGST@9%%\t\t\t\t\t\t\t\t %.2f\n",(net*9)/100);
    printf("SGST@9%%\t\t\t\t\t\t\t\t %.2f\n",(net*9)/100);
    printf("-------------------------------------------------------------------------\n");
    printf("Grand Total\t\t\t\t\t\t\t\033[0;32m %.2f\n",net + (net*9)/50);
    reset();
    printf("-------------------------------------------------------------------------\n");
    yellow();
    printf("\n===========================================================================\n\n");
    reset();
    total += net + (net*9)/50;
    temp = temp -> next;
}
printf("Total Income Till now: \033[0;32m%.2f\n\n", total);
reset();
}
void searchInvoice(){
    char s[20];
    printf("Enter the name of customer: ");
    green();
    scanf("%s", s);
    reset();
    struct customer *temp;
    temp = c_h;
    while(temp != NULL){
        if(strcmp(temp -> name, s) == 0){
            printf("\n<---------------------------- \033[0;32mInvoice Founded\033[0m ---------------------------->\n\n");
            display_invoice(temp);
            return;
        }
        temp = temp -> next;
    }
    red();
    printf("\n!!NO INVOICE FOUND WITH THE GIVEN NAME!!\n\n");
    reset();
}
void update_list(){
     int u_check, d_check;
     while(1){
     printf("\nFollowing are the options available: \n");
     cyan();
     printf("\n1. Add\n2. Delete\n");
     reset();
     printf("Enter your choice: ");
     green();
     scanf("%d", &u_check);
     reset();
     switch(u_check){
     case 1:
         w_count++;
         w_c = (struct w*)malloc(sizeof(struct w));
         w_c -> sr = w_count;
         printf("\nEnter name of the customer: ");
         green();
         scanf("%s", w_c -> name);
         reset();
         printf("Enter the member: ");
         green();
         scanf("%d", &w_c -> member);
         reset();
         if(w_h == NULL){
            w_h = w_c;
            w_t = w_c;
            w_h -> next = w_c;
            w_h -> prev = w_c;
         }
         else{
            w_t -> next = w_c;
            w_c -> prev = w_t;
            w_t = w_c;
            w_h -> prev = w_c;
            w_c -> next = w_h;
         }
         green();
         printf("\nWaiting List updated!\n");
         reset();
         display_wait();
         break;
     case 2:
          if(w_count == 0){
                yellow();
                printf("\nList is already empty!\n");
                reset();
            }
            else{
                printf("\n");
                    display_wait();
            printf("\nFollowing are the options available: \n");
            cyan();
        printf("\n1. Delete First name\n2. Delete Last name\n\n");
        reset();
        printf("Enter your choice: ");
        green();
        scanf("%d", &d_check);
        reset();
        switch(d_check){
        case 1:
                w_count--;
                struct w *t;
                t = w_h;
                if(w_count != 0){
                w_h -> prev -> next = w_h -> next;
                w_h -> next -> prev = w_h -> prev;
                w_h = w_h -> next;
                t = NULL;
                struct w *temp;
                temp = w_h;
                while(1){
                    temp -> sr -= 1;
                    temp = temp -> next;
                    if(temp == w_h) break;
                }
                }
                else{
                    w_h = NULL;
                }
                green();
                printf("\nDeleted successfully!\n");
                reset();
               break;
        case 2:
                w_count--;
                struct w *temp;
                temp = w_h -> prev;
                if(w_count != 0){
                temp -> prev -> next = w_h;
                w_h -> prev = temp -> prev;
                temp = NULL;
                }
                else{
                    w_h = NULL;
                }
                green();
                printf("\nDeleted successfully!\n");
                reset();
                break;
        }
        display_wait();
    }
     }
      int c;
             printf("Do you want to continue Updating List(YES - 1 / NO - 2): ");
             green();
             scanf("%d", &c);
             reset();
         if(c == 2) return;
}
}
void update_menu(){
int u_check, d_check = 1;
     while(1){
     printf("\nFollowing are the options available: \n");
     cyan();
     printf("\n1. Add\n2. Delete\n");
     reset();
     printf("Enter your choice: ");
     green();
     scanf("%d", &u_check);
     reset();
     switch(u_check){
     case 1:
         m_count++;
         m_c = (struct menu*)malloc(sizeof(struct menu));
         m_c -> sr = m_count;
         printf("\nEnter name of the Item: ");
         green();
         scanf("%s", m_c -> item);
         reset();
         printf("Enter the price of the Item: ");
         green();
         scanf("%f", &m_c -> price);
         reset();
         if(m_h == NULL){
            m_h = m_c;
            m_t = m_c;
         }
         else{
            m_t -> next = m_c;
            m_c -> prev = m_t;
            m_t = m_c;
            m_h -> prev = m_c;
            m_c -> next = m_h;
         }
         green();
         printf("\nList updated!\n");
         reset();
         display();
         break;
     case 2:
          if(m_count == 0){
                yellow();
                printf("\nList is already empty!\n");
                reset();
            }
            else{
                printf("\n");
                display();
                char s[100];
                printf("Enter the name of the item you want to delete: ");
                green();
                scanf("%s", s);
                reset();
                struct menu *temp;
                temp = m_h;
                while(temp != NULL){
                    if(strcmp(s,temp -> item) == 0){
                        m_count--;
                        struct menu *t;
                        t = temp;
                        while(t != NULL){
                            t = t -> next;
                            if(t == m_h) break;
                            t -> sr -= 1;
                        }
                        temp -> prev -> next = temp -> next;
                        temp -> next -> prev = temp -> prev;
                        if(temp == m_h){
                            m_h = temp -> next;
                        }
                        temp = NULL;
                        break;
                    }
                    temp = temp -> next;
                    if(temp == m_h){
                        red();
                        printf("NO SUCH ITEM EXIST!!\n");
                        d_check = 0;
                        reset();
                        break;
                    }
                }
                if(d_check){
                green();
                printf("\nDeleted successfully!\n");
                reset();
                display();
                }
    }
     }
      int c;
             printf("Do you want to continue Updating List(YES - 1 / NO - 2): ");
             green();
             scanf("%d", &c);
             reset();
         if(c == 2) return;
}
}
int conti(int n){
             int c;
             if(n == 1){
             printf("Do you want to continue in Customer software(YES - 1 / NO - 2): ");
             green();
             scanf("%d", &c);
             reset();
             return c;
             }
             else{
             printf("Do you want to continue in Management software(YES - 1 / NO - 2): ");
             green();
             scanf("%d", &c);
             reset();
             return c;
             }
}
int conti_order(){
             int c;
             printf("Do you want to continue ordering (YES - 1 / NO - 2): ");
             green();
             scanf("%d", &c);
             reset();
             return c;
}
int main(){
    int soft_check, c_check, m_check, flag = 0;
    char a[][100] = {"Tikka_Burger", "Veg.Burger", "French_Fries", "Veg.Momos", "Falafel", "Veg.Frankie", "Cheese_frankie", "Veg.sandwich", "Veg.Maggi", "Cheese_maggi"};
    int p[10] = {70, 40, 90, 100, 150, 60, 70, 45, 50, 60};
    for(int i = 0; i < 10; ++i){
        m_count++;
        m_c = (struct menu *)malloc(sizeof(struct menu));
        if(m_h == NULL){
            m_h = m_c;
            strcpy(m_c -> item, a[i]);
            m_c -> price = p[i];
            m_c -> sr = m_count;
            m_t = m_c;
        }
        else{
            m_h -> prev = m_c;
            m_t -> next = m_c;
            m_c -> prev = m_t;
            strcpy(m_c -> item, a[i]);
            m_c -> price = p[i];
            m_c  -> sr = m_count;
            m_t = m_c;
            m_c -> next = m_h;
        }
    }
    software:
    printf("\n\033[0;34m<-------------------------------------- \033[1;31mWelcome to \"MADOVER GRILLS\"\033[0;34m-------------------------------------->\033[0m\n\n");
    printf("In which software you want to enter: \n");
    purple();
    printf("1. Customer Sotware\n2. Management Software\n\n");
    reset();
    printf("Enter your choice: ");
    green();
    scanf("%d", &soft_check);
    reset();
    switch(soft_check){
        case 1:
         c_c = (struct customer*)malloc(sizeof(struct customer));
         printf("Enter your Name: ");
            green();
            scanf("%s", c_c -> name);
            fflush(stdout);
            reset();
            do{
            flag = 0;
            printf("Enter your Mobile Number: ");
            green();
            scanf("%s", &c_c -> no);
            reset();
            for(int i = 0; i < strlen(c_c -> no); ++i){
                if((c_c -> no[i]) < '0' && (c_c -> no[i]) > '9'){
                    flag = 1;
                    break;
                }
            }
            if(flag == 0 && strlen(c_c -> no) == 10){
            if(c_h == NULL){
                c_h = c_c;
                c_t = c_c;
            }
            else{
                c_t -> next = c_c;
                c_c -> prev = c_t;
                c_t = c_c;
            }
            }
            else{
                red();
                printf("Enter a VALID NUMBER!!\n");
                reset();
            }
            }while(strlen(c_c -> no) != 10 || flag == 1);
         while(1){
         printf("\nFollowing is the list of services provided by the restaurant: \n");
         cyan();
         printf("\n1. Display menu\n2. Order the food\n3. Display Waiting list\n4. Show Invoice\n5. Exit\n\n");
         reset();
         printf("\nEnter your choice: ");
         green();
         scanf("%d", &c_check);
         reset();
         switch(c_check){
         case 1:
             display();
             break;
         case 2:
            display();
            odd:
                o_item();
                int c1 = conti_order();
                if(c1 == 1){
                    goto odd;
                }
                break;
         case 3:
             display_wait();
             break;
         case 4:
            display_invoice(c_c);
            break;
         case 5:
            if(c_c -> o_h == NULL){
            display_invoice(c_c);
            yellow();
            printf("\nThank You for visiting MADOVER GRILLS!!\nVisit Agian!!\n");
            reset();
            }
            else{
            printf("<-------------------------------------- \033[0;32mFinal Invoice\033[0m -------------------------------------->\n\n");
            display_invoice(c_c);
            yellow();
            printf("Thank You for visiting MADOVER GRILLS!!\nVisit Agian!!\n");
            reset();
            }
            goto software;
            break;
         default:
            red();
            printf("Enter a Valid Choice!!\n");
            reset();
            break;
         }
         int c = conti(1);
         if(c == 2){
                goto software;
             }
         }
         break;
         case 2:
         while(1){
         printf("\nFollowing is the list of services provided by the restaurant: \n");
         cyan();
         printf("\n1. Show all Invoice.\n2. Search Invoice\n3. Update waiting List\n4. Update menu\n5. Exit\n");
         reset();
         printf("\nEnter your choice: ");
         green();
         scanf("%d", &m_check);
         reset();
         switch(m_check){
         case 1:
             showInvoice();
             break;
         case 2:
             searchInvoice();
             break;
         case 3:
            update_list();
            break;
         case 4:
            update_menu();
         }
         int c = conti(2);
         if(c == 2){
                goto software;
             }
         }
         break;
    }
}

