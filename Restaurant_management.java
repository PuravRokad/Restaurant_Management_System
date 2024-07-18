import java.util.*;
import java.util.LinkedList;
import java.time.format.DateTimeFormatter;
import java.time.LocalDateTime;
import java.util.regex.*;

class customer{
    String name;
    String number;
}
class order extends customer{
    float total = 0;
    LinkedList<Integer> sr = new LinkedList<>();
    LinkedList<String> o_name = new LinkedList<>();
    LinkedList<Integer> qty = new LinkedList<>();
    LinkedList<Integer> price = new LinkedList<>();
    float total(){
        total += (qty.getLast()*price.getLast());
        return total;
    }
}
class menu{
    LinkedList<Integer> sr = new LinkedList<>();
    LinkedList<String> list = new LinkedList<>();
    LinkedList<Integer> price = new LinkedList<>();
}
class wait_list{
    LinkedList<String> name = new LinkedList<>();
    LinkedList<Integer> member = new LinkedList<>();
}
public class Restaurant_management{
    static int add_menu(menu m, int m_count){
        m_count++;
        Scanner sc = new Scanner(System.in);
        System.out.println("Enter the name of the Item: ");
        m.list.add(sc.nextLine());
        System.out.println("Enter the price of the Item: ");
        m.price.add(sc.nextInt());
        m.sr.add(m_count);
        System.out.println("Menu Updated Successfully!!");
        display_menu(m);
        return m_count;
    }
    static int delete_menu(menu m, int m_count){
        Scanner sc = new Scanner(System.in);
        display_menu(m);
        System.out.println("Enter the name of the Item you want to remove: ");
        String s = sc.nextLine();
        for(int i = 0; i < m.list.size(); ++i){
            if(s.equalsIgnoreCase(m.list.get(i))){
                m.list.remove(i);
                m.price.remove(i);
                for(int j = i; j < m.sr.size(); ++j){
                    m.sr.set(j, m.sr.get(j));
                }
                m_count--;
                System.out.println("Menu Updated!!");
                display_menu(m);
                return m_count;
            }
        }
        System.out.println("Item doesn't exist!!");
        return m_count;
    }

    static int update_menu(menu m, int m_count){
        Scanner sc = new Scanner(System.in);
        while(true) {
            System.out.println("1. Add\n2. Remove");
            System.out.println("Enter your choice: ");
            int w_choice = sc.nextInt();
            switch (w_choice) {
                case 1:
                    m_count = add_menu(m, m_count);
                    break;
                case 2:
                    m_count = delete_menu(m, m_count);
                    break;
            }
            int a;
            System.out.println("Do you want to continue Updating(YES - 1 / NO - 2): ");
            a = sc.nextInt();
            if(a == 2){
                break;
            }
        }
        return m_count;
    }
    static void add_wait(wait_list w){
        Scanner sc = new Scanner(System.in);
        System.out.println("Enter the name of the customer: ");
        w.name.add(sc.nextLine());
        System.out.println("Enter the number of members: ");
        w.member.add(sc.nextInt());
        System.out.println("Waiting list Updated successfully!!");
        show_wait(w);
    }
    static void delete_wait(wait_list w){
        Scanner sc = new Scanner(System.in);
        String s;
        show_wait(w);
        if(w.name.size() != 0) {
            System.out.printf("Enter name of the customer you want to remove: \n");
            s = sc.nextLine();
            for (int i = 0; i < w.name.size(); ++i) {
                if (s.equalsIgnoreCase(w.name.get(i))) {
                    w.name.remove(i);
                    w.member.remove(i);
                    System.out.println("List Updated!!");
                    show_wait(w);
                    return;
                }
            }
            System.out.println("customer doesn't exist!!");
        }
    }
    static void update_wait(wait_list w){
        Scanner sc = new Scanner(System.in);
        while(true) {
            System.out.println("1. Add\n2. Remove");
            System.out.println("Enter your choice: ");
            int w_choice = sc.nextInt();
            switch (w_choice) {
                case 1:
                    add_wait(w);
                    break;
                case 2:
                    delete_wait(w);
                    break;
            }
            int a;
            System.out.println("Do you want to continue Updating(YES - 1 / NO - 2): ");
            a = sc.nextInt();
            if(a == 2){
                break;
            }
        }

    }
    static void search_invoice(int size, LinkedList<order> cost_list){
        Scanner sc = new Scanner(System.in);
        System.out.println("Enter the name of customer whose Invoice you want: ");
        String s = sc.nextLine();
        for(int i = 0; i < size; ++i){
            if(s.equalsIgnoreCase(cost_list.get(i).name)){
                System.out.println(GREEN_BOLD + "<--------------------------------- INVOICE FOUNDED --------------------------------->" + RESET);
                show_invoice(i, i+1, cost_list);
                return;
            }
        }
        System.out.println( RED_BOLD +"NO INVOICE WITH SUCH NAME FOUND!!" + RESET);
        return;
    }
    static void show_wait(wait_list wait){
        if(wait.name.size() == 0){
            System.out.printf(GREEN_BOLD + "There is No Waiting!\n" + RESET);
        }
        else{
            System.out.print(BLACK_BOLD);
            System.out.printf("<------------------------------------ Waiting List ------------------------------------>\n");
            System.out.printf("----------------------------------------------------------------------------------------\n");
            System.out.printf("Sr.No.\t\t\t\t\t\tName\t\t\t\t\t\t\t\t Members\n");
            System.out.printf("----------------------------------------------------------------------------------------\n");
            for(int i = 0; i < wait.name.size(); ++i){
                int space = 20 - wait.name.get(i).length();
                System.out.printf("%d\t\t\t\t\t\t\t%s", i + 1, wait.name.get(i));
                for(int j = 0; j < space; ++j){
                    System.out.print(" ");
                }
                System.out.printf("\t\t\t\t\t%d\n", wait.member.get(i));
            }
            System.out.print(RESET);
        }
    }
    static float show_invoice(int a, int size, LinkedList<order> cost_list){
        float all_total = 0;
        for(int i = a; i < size; ++i) {
            if(cost_list.get(i).o_name.size() == 0){
                System.out.println(WHITE_BOLD + "There is " + RED_BOLD + "NO INVOICE" + WHITE_BOLD + " since you ordered" + RED_BOLD + " NOTHING!!" + RESET);
                break;
            }
            System.out.print(RED_BOLD + "\t\t\t\t  🅼🅰🅳🅾🆅🅴🆁 🅶🆁🅸🅻🅻🆂 \t\t\t\t\n" + RESET);
            System.out.print("\t\t\t\t--------------------------\t\t\t\t\n");
            DateTimeFormatter dtf = DateTimeFormatter.ofPattern("yyyy/MM/dd");
            LocalDateTime now = LocalDateTime.now();
            System.out.println(BLUE_BOLD + "Date: " + WHITE_BOLD + dtf.format(now));
            System.out.println(BLUE_BOLD + "Invoice to: " + WHITE_BOLD + cost_list.get(i).name);
            System.out.println(BLUE_BOLD + "Mobile No.: " + WHITE_BOLD + cost_list.get(i).number + BLACK_BOLD);
            System.out.println("--------------------------------------------------------------");
            System.out.println(BLACK_BOLD + "Items\t\t\t\t\t\tQty.\t\t\t\t Price" + BLACK_BOLD);
            System.out.println("--------------------------------------------------------------\n");
            System.out.print(BLACK_BOLD);
            for(int j = 0; j < cost_list.get(i).o_name.size(); ++j) {
                int space = 20 - cost_list.get(i).o_name.get(j).length();
                System.out.printf(cost_list.get(i).o_name.get(j));
                for (int k = 0; k < space; ++k) {
                    System.out.print(" ");
                }
                System.out.printf("\t\t%d\t\t\t\t\t %.2f\n", cost_list.get(i).qty.get(j), cost_list.get(i).qty.get(j)*(float)cost_list.get(i).price.get(j));
            }
            System.out.print(BLACK_BOLD);
            System.out.print("\n-------------------------------------------------------------\n");
            System.out.print(BLACK_BOLD);
            System.out.printf("Subtotal\t\t\t\t\t\t\t\t\t\t %.2f\n", cost_list.get(i).total);
            float discount = (cost_list.get(i).total*10)/100;
            System.out.printf("Discount@10%%\t\t\t\t\t\t\t\t\t %.2f\n",discount);
            System.out.print(BLACK_BOLD);
            System.out.printf("        \t\t\t\t\t\t\t\t       ------------\n");
            float net = cost_list.get(i).total - discount;
            System.out.print(BLACK_BOLD);
            System.out.printf("Net Total\t\t\t\t\t\t\t\t\t\t %.2f\n",net);
            System.out.printf("CGST@9%%\t\t\t\t\t\t\t\t\t\t\t %.2f\n",(net*9)/100);
            System.out.printf("SGST@9%%\t\t\t\t\t\t\t\t\t\t\t %.2f\n",(net*9)/100);
            System.out.print(BLACK_BOLD);
            System.out.print("---------------------------------------------------------------\n");
            System.out.print(BLACK_BOLD);
            System.out.printf("Grand Total\t\t\t\t\t\t\t\t\t\t");
            System.out.print(GREEN_BOLD);
            System.out.printf(" %.2f\n",net + (net*9)/50);
            System.out.print(BLACK_BOLD);
            System.out.print("---------------------------------------------------------------\n");
            all_total += net + (net*9)/50;
            if(a != size - 1) {
                System.out.print("\n===========================================================================\n\n");
            }
            System.out.print(RESET);
        }
        return all_total;
    }
    static int c_order(order c_o, menu m1, int count){
        Scanner sc = new Scanner(System.in);
        int sr;
        System.out.println("Enter the Sr.No. of the item you want to enter: ");
        sr = sc.nextInt();
        for(int i = 0; i < m1.list.size(); ++i){
            if(sr == m1.sr.get(i)){
                int q, check = 0;
                System.out.println("Enter the quantity: ");
                q = sc.nextInt();
                for(int j = 0; j < c_o.o_name.size(); ++j){
                    if(c_o.o_name.get(j) == m1.list.get(i)){
                        c_o.qty.set(j, c_o.qty.get(j) + q);
                        check++;
                    }
                }
                if(check == 0) {
                    c_o.qty.add(q);
                    c_o.o_name.add(m1.list.get(i));
                    count++;
                    c_o.sr.add(count);
                    c_o.price.add(m1.price.get(i));
                }
                c_o.total();
                System.out.println(BLACK_BOLD + "Order Added!");
                System.out.println("Amount of Item Added: " + PURPLE_BOLD + q * m1.price.get(i));
                System.out.println(BLACK_BOLD + "Amount till Now: " + GREEN_BOLD + c_o.total);
                System.out.print(RESET);
                return count;
            }
        }
        System.out.println(RED_BOLD + "Enter a valid Sr.No.!!" + RESET);
        return count;
    }
    static void display_menu(menu m_display){
        System.out.println(BLUE_BOLD + "<----------------------------------- " + RED_BOLD + "Menu" + BLUE_BOLD + " ----------------------------------->" + RESET);
        System.out.println( BLACK_BOLD + "------------------------------------------------------------------------------" + RESET);
        System.out.println(CYAN_BOLD + "Sr.No.\t\t\t\t\tItem\t\t\t\t\t\t\tPrice(in Rs.)" + RESET);
        System.out.println(BLACK_BOLD + "------------------------------------------------------------------------------" + RESET);
        for(int i = 0; i < m_display.list.size(); ++i) {
            int space = 20 - m_display.list.get(i).length();
            System.out.print(BLACK_BOLD + m_display.sr.get(i) + "\t\t\t\t\t" + m_display.list.get(i));
            for(int j = 0; j < space; ++j){
                System.out.print(" ");
            }
            System.out.print(GREEN_BOLD);
            System.out.print("\t\t\t\t\t");
            System.out.printf("%.2f\n",(float)m_display.price.get(i));
            System.out.print(RESET);
        }
        System.out.println(RESET);
    }
    static int conti(int n){
        int c;
        Scanner sc = new Scanner(System.in);
        if(n == 1){
            System.out.println("Do you want to continue in Customer software(YES - 1 / NO - 2): ");
            c = sc.nextInt();
            return c;
        }
        else{
            System.out.println("Do you want to continue in Management software(YES - 1 / NO - 2): ");
            c = sc.nextInt();
            return c;
        }
    }
    public static boolean isValidMobileNo(String str)
    {
        Pattern ptrn = Pattern.compile("(0/91)?[7-9][0-9]{9}");
        Matcher match = ptrn.matcher(str);
        return (match.find() && match.group().equals(str));
    }
    public static final String BLACK_BACKGROUND = "\u001B[40m";
    public static final String RED_BACKGROUND = "\u001B[41m";
    public static final String GREEN_BACKGROUND = "\u001B[42m";
    public static final String YELLOW_BACKGROUND = "\u001B[43m";
    public static final String BLUE_BACKGROUND = "\u001B[44m";
    public static final String PURPLE_BACKGROUND = "\u001B[45m";
    public static final String CYAN_BACKGROUND = "\u001B[46m";
    public static final String WHITE_BACKGROUND = "\u001B[47m";
    public static final String RESET = "\u001B[0m";
    public static final String BLACK = "\u001B[30m";
    public static final String RED = "\u001B[31m";
    public static final String GREEN = "\u001B[32m";
    public static final String YELLOW = "\u001B[33m";
    public static final String BLUE = "\u001B[34m";
    public static final String PURPLE = "\u001B[35m";
    public static final String CYAN = "\u001B[36m";
    public static final String WHITE = "\u001B[37m";
    public static final String BLACK_BOLD = "\033[1;30m";  // BLACK
    public static final String RED_BOLD = "\033[1;31m";    // RED
    public static final String GREEN_BOLD = "\033[1;32m";  // GREEN
    public static final String YELLOW_BOLD = "\033[1;33m"; // YELLOW
    public static final String BLUE_BOLD = "\033[1;34m";   // BLUE
    public static final String PURPLE_BOLD = "\033[1;35m"; // PURPLE
    public static final String CYAN_BOLD = "\033[1;36m";   // CYAN
    public static final String WHITE_BOLD = "\033[1;37m";  // WHITE
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        menu m = new menu();
        wait_list w = new wait_list();
        String s[] = {"Tikka_Burger", "Veg.Burger", "French_Fries", "Veg.Momos", "Falafel", "Veg.Frankie", "Cheese_frankie", "Veg.sandwich", "Veg.Maggi", "Cheese_maggi"};
        int p[] = {70, 40, 90, 100, 150, 60, 70, 45, 50, 60};
        for (int i = 0; i < 10; ++i) {
            m.list.add(s[i]);
            m.price.add(p[i]);
            m.sr.add(i + 1);
        }
        LinkedList<order> customer_list = new LinkedList<order>();
        int m_count = 10;
        //display_menu(m);
        while (true) {
            //System.out.println(YELLOW_BACKGROUND);
            System.out.println(BLUE_BOLD + "\n<-------------------------------------- " + RED_BOLD + "🔥 Welcome to 🅼🅰🅳🅾🆅🅴🆁 🅶🆁🅸🅻🅻🆂 🔥"+ BLUE_BOLD +" -------------------------------------->\n");
            System.out.println(PURPLE_BOLD +"1. Customer Software");
            System.out.println(PURPLE_BOLD + "2. Management Software");
            System.out.println(RESET + "Enter your choice: ");
            int soft_choice = sc.nextInt();
            int c_choice, m_choice;
            switch (soft_choice) {
                case 1:
                    int o_count = 0;
                    order c = new order();
                    customer_list.add(c);
                    System.out.println("Enter your name: ");
                    //System.out.flush();
                    sc.nextLine();
                    c.name = sc.nextLine();
                    while(true) {
                        System.out.println("Enter your number: ");
                        c.number = sc.nextLine();
                        if (isValidMobileNo(c.number)) {
                            while (true) {
                                System.out.println("\nFollowing is the list of services provided by the restaurant:");
                                System.out.println(CYAN_BOLD + "1. Display menu\n2. Order the food\n3. Display Waiting list\n4. Show Invoice\n5. Exit\n" + RESET);
                                System.out.println("Enter your choice: ");
                                c_choice = sc.nextInt();
                                switch (c_choice) {
                                    case 1:
                                        display_menu(m);
                                        break;
                                    case 2:
                                        while (true) {
                                            display_menu(m);
                                            o_count = c_order(c, m, o_count);
                                            int c1;
                                            System.out.println("Do you want to continue ordering (YES - 1 / NO - 2): ");
                                            c1 = sc.nextInt();
                                            if (c1 == 2) {
                                                break;
                                            }
                                        }
                                        break;
                                    case 3:
                                        show_wait(w);
                                        break;
                                    case 4:
                                        show_invoice(customer_list.size() - 1, customer_list.size(), customer_list);
                                        break;
                                    case 5:
                                        System.out.println( YELLOW_BOLD + "<------------------------ Final Invoice ------------------------>" + RESET);
                                        show_invoice(customer_list.size() - 1, customer_list.size(), customer_list);
                                        System.out.printf(BLACK_BOLD + "Thank You for visiting MADOVER GRILLS!!\nVisit Agian!!\n" + RESET);
                                        break;
                                    default:
                                        System.out.println("Enter a valid choice!!");
                                        break;
                                }
                                int a = conti(1);
                                if (a == 2) {
                                    System.out.println("\033[H\033[2J");
                                    System.out.flush();
                                    break;
                                }
                            }
                            break;
                        }
                        else{
                            System.out.println(YELLOW_BOLD + "Please enter a Valid Mobile Number!!" + RESET);
                        }
                    }
                    break;
                case 2:
                    while (true) {
                        System.out.println("\nFollowing is the list of services provided by the restaurant:");
                        System.out.println(CYAN_BOLD + "1. Show all Invoice\n2. Search Invoice\n3. Update Waiting list\n4. Update Menu\n5. Exit\n" + RESET);
                        System.out.println("Enter your choice: ");
                        m_choice = sc.nextInt();
                        switch (m_choice) {
                            case 1:
                                float all_total = show_invoice(0, customer_list.size(), customer_list);
                                System.out.println(BLACK_BOLD +"Total Income till Now: "+ GREEN_BOLD + "Rs."+ all_total + RESET);
                                break;
                            case 2:
                                search_invoice(customer_list.size(), customer_list);
                                break;
                            case 3:
                                update_wait(w);
                                break;
                            case 4:
                                m_count = update_menu(m, m_count);
                        }
                        int a = conti(2);
                        if (a == 2) {
                            System.out.println("\033[H\033[2J");
                            System.out.flush();
                            break;
                        }
                    }
            }
        }
    }
}





