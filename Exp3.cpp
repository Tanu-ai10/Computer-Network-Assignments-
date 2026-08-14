#include <iostream>
using namespace std;

int main() {
    int a, b, c, d;
    char ch;

    cout << "Enter IP Address (format: x.x.x.x): ";
    cin >> a >> ch >> b >> ch >> c >> ch >> d;

    if (a >= 1 && a <= 126) {
        cout << "\n========== CLASS A ==========";
        cout << "\nIP Class              : A";
        cout << "\nAddress Range         : 1.0.0.0 - 126.255.255.255";
        cout << "\nDefault Subnet Mask   : 255.0.0.0 (/8)";
        cout << "\nNetwork Bits          : 8";
        cout << "\nHost Bits             : 24";

        cout << "\n\nNumber of Networks    : 2^7 - 2 = 126";
        cout << "\nReason                :";
        cout << "\n- First bit is fixed as 0 for Class A.";
        cout << "\n- Remaining 7 bits represent the Network ID.";
        cout << "\n- Network 0 is reserved.";
        cout << "\n- Network 127 is reserved for Loopback.";

        cout << "\n\nNumber of Hosts/Network : 2^24 - 2 = 16,777,214";
        cout << "\nFormula                 : 2^(Host Bits) - 2";
        cout << "\nReason for -2           :";
        cout << "\n- One address is the Network Address (all host bits = 0).";
        cout << "\n- One address is the Broadcast Address (all host bits = 1).";
        cout << "\n- These cannot be assigned to hosts.";
    }

    else if (a == 127) {
        cout << "\n========== LOOPBACK ==========";
        cout << "\nIP Class              : Loopback";
        cout << "\nAddress Range         : 127.0.0.0 - 127.255.255.255";
        cout << "\nPurpose               : Used for localhost/testing.";
        cout << "\nDefault Subnet Mask   : 255.0.0.0 (/8)";
    }

    else if (a >= 128 && a <= 191) {
        cout << "\n========== CLASS B ==========";
        cout << "\nIP Class              : B";
        cout << "\nAddress Range         : 128.0.0.0 - 191.255.255.255";
        cout << "\nDefault Subnet Mask   : 255.255.0.0 (/16)";
        cout << "\nNetwork Bits          : 16";
        cout << "\nHost Bits             : 16";

        cout << "\n\nNumber of Networks    : 2^14 = 16,384";
        cout << "\nReason                :";
        cout << "\n- First 2 bits are fixed as 10.";
        cout << "\n- Remaining 14 bits represent the Network ID.";

        cout << "\n\nNumber of Hosts/Network : 2^16 - 2 = 65,534";
        cout << "\nFormula                 : 2^(Host Bits) - 2";
        cout << "\nReason for -2           :";
        cout << "\n- One address is the Network Address.";
        cout << "\n- One address is the Broadcast Address.";
        cout << "\n- These two addresses cannot be assigned to hosts.";
    }

    else if (a >= 192 && a <= 223) {
        cout << "\n========== CLASS C ==========";
        cout << "\nIP Class              : C";
        cout << "\nAddress Range         : 192.0.0.0 - 223.255.255.255";
        cout << "\nDefault Subnet Mask   : 255.255.255.0 (/24)";
        cout << "\nNetwork Bits          : 24";
        cout << "\nHost Bits             : 8";

        cout << "\n\nNumber of Networks    : 2^21 = 2,097,152";
        cout << "\nReason                :";
        cout << "\n- First 3 bits are fixed as 110.";
        cout << "\n- Remaining 21 bits represent the Network ID.";

        cout << "\n\nNumber of Hosts/Network : 2^8 - 2 = 254";
        cout << "\nFormula                 : 2^(Host Bits) - 2";
        cout << "\nReason for -2           :";
        cout << "\n- One address is the Network Address.";
        cout << "\n- One address is the Broadcast Address.";
        cout << "\n- These two addresses cannot be assigned to hosts.";
    }

    else if (a >= 224 && a <= 239) {
        cout << "\n========== CLASS D ==========";
        cout << "\nIP Class            : D (Multicast)";
        cout << "\nAddress Range       : 224.0.0.0 - 239.255.255.255";
        cout << "\nDefault Subnet Mask : Not Applicable";
        cout << "\nPurpose             : Used for Multicasting.";
    }

    else if (a >= 240 && a <= 255) {
        cout << "\n========== CLASS E ==========";
        cout << "\nIP Class            : E (Experimental)";
        cout << "\nAddress Range       : 240.0.0.0 - 255.255.255.255";
        cout << "\nDefault Subnet Mask : Not Applicable";
        cout << "\nPurpose             : Reserved for Research and Experimental use.";
    }

    else {
        cout << "\nInvalid IP Address!";
    }

    return 0;
}
