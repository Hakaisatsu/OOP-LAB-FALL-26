#include <iostream>
#include <string>
using namespace std;

class Order {
public:
    int order_id, price, quantity;
    float float_price;
    string item_name;

    Order() {
        order_id = price = quantity = 0;
        float_price = 0;
    }

    void Input() {
        cout << "enter item name: ";
        cin >> item_name;
        cout << "enter price: ";
        cin >> price;
        cout << "enter quantity: ";
        cin >> quantity;

        if (price < 0 || quantity <= 0) {
            cout << "invalid price or quantity\n";
            price = 0;
            quantity = 1;
        }
        float_price = price;
    }

    void Display() {
        cout << "order id: " << order_id
             << ", item: " << item_name
             << ", price: " << price
             << ", quantity: " << quantity << '\n';
    }

    int CalculateBill(int p, int q) {
        return p * q;
    }

    float CalculateBill(int p, int q, int discount) {
        return p * q * (100 - discount) / 100.0f;
    }

    float CalculateBill(float p, int q) {
        return p * q;
    }

    int CalculateBill(int p1, int q1, int p2, int q2) {
        return p1 * q1 + p2 * q2;
    }
};

int main() {
    Order orders[50], calculator;
    int count = 0, next_id = 1, choice, id, index;

    do {
        cout << "\n1. add order\n2. update order\n3. delete order\n"
             << "4. search order\n5. display order\n6. display all\n"
             << "7. calculate bill\n8. exit\nchoice: ";
        cin >> choice;

        if (choice == 1) {
            if (count == 50) {
                cout << "order list is full\n";
                continue;
            }

            orders[count].order_id = next_id++;
            cout << "order id: " << orders[count].order_id << '\n';
            orders[count].Input();
            count++;
        }
        else if (choice >= 2 && choice <= 5) {
            if (count == 0) {
                cout << "no orders available\n";
                continue;
            }

            cout << "enter order id: ";
            cin >> id;
            index = -1;

            for (int i = 0; i < count; i++)
                if (orders[i].order_id == id) index = i;

            if (index == -1) {
                cout << "order not found\n";
                continue;
            }

            if (choice == 2) orders[index].Input();
            else if (choice == 3) {
                for (int i = index; i < count - 1; i++)
                    orders[i] = orders[i + 1];
                count--;
                cout << "order deleted\n";
            }
            else orders[index].Display();
        }
        else if (choice == 6) {
            if (count == 0) cout << "no orders available\n";
            for (int i = 0; i < count; i++) orders[i].Display();
        }
        else if (choice == 7) {
            int method, p, q, discount, p2, q2;
            float fp;

            cout << "1. integer bill\n2. bill with discount\n"
                 << "3. floating-point bill\n4. two-item bill\nchoice: ";
            cin >> method;

            if (method == 1) {
                cout << "enter price and quantity: ";
                cin >> p >> q;
                if (p < 0 || q <= 0) cout << "invalid values\n";
                else cout << "total bill: "
                          << calculator.CalculateBill(p, q) << '\n';
            }
            else if (method == 2) {
                cout << "enter price, quantity and discount percentage: ";
                cin >> p >> q >> discount;
                if (p < 0 || q <= 0 || discount < 0 || discount > 100)
                    cout << "invalid values\n";
                else cout << "discounted bill: "
                          << calculator.CalculateBill(p, q, discount) << '\n';
            }
            else if (method == 3) {
                cout << "enter floating-point price and quantity: ";
                cin >> fp >> q;
                if (fp < 0 || q <= 0) cout << "invalid values\n";
                else cout << "floating-point bill: "
                          << calculator.CalculateBill(fp, q) << '\n';
            }
            else if (method == 4) {
                cout << "enter first price and quantity: ";
                cin >> p >> q;
                cout << "enter second price and quantity: ";
                cin >> p2 >> q2;

                if (p < 0 || p2 < 0 || q <= 0 || q2 <= 0)
                    cout << "invalid values\n";
                else cout << "combined bill: "
                          << calculator.CalculateBill(p, q, p2, q2) << '\n';
            }
            else cout << "invalid choice\n";
        }
    } while (choice != 8);

    return 0;
}