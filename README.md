# 🛡️ ESP32 Based Lineman Security System

An advanced IoT-based security solution designed for electrical linemen to prevent unauthorized access to high-voltage lines or industrial machinery. The system utilizes **Two-Factor Authentication (2FA)** via OTP sent over GSM to ensure maximum safety during maintenance.

---

### 🚀 Key Features
* **OTP-Based Authentication**: Generates a unique 4-digit One-Time Password for every access request.
* **GSM Connectivity**: Uses SIM800L to send OTPs directly to the supervisor's or lineman's mobile device .
* **Local UI & Feedback**: 16x2 LCD for status messages and a buzzer for audible confirmation/warnings .
* **Secure Control**: Industrial-grade relay module to manage power state (Lock/Unlock).
* **Robust Input**: 4x4 Matrix Keypad for manual OTP entry.

---

### 🛠️ Hardware Components
| Component | Description |
| :--- | :--- |
| **ESP32** | The brain of the system, handling logic and communication. |
| **SIM800L GSM Module** | Handles SMS transmission and reception. |
| **16x2 LCD (I2C)** | Displays system states (e.g., "SYSTEM LOCKED", "ENTER OTP").|
| **4x4 Keypad** | Used for user input of the OTP. |
| **5V Relay Module** | Controls the electrical load/line connection. |
| **Buzzer** | Provides audio alerts for success or failure. |
| **Li-ion Battery** | Power source for portability and reliability . |

---

### 🔌 Pin Configuration
| Hardware | ESP32 Pin |
| :--- | :--- |
| **SIM800L TX** | GPIO 16 (RX2) |
| **SIM800L RX** | GPIO 17 (TX2) |
| **I2C SDA** | GPIO 21 |
| **I2C SCL** | GPIO 22 |
| **Relay Signal** | GPIO 18 |
| **Buzzer** | GPIO 19 |

---

### 📖 Workflow
1.  **System Idle**: The LCD displays the current status (LOCK/UNLOCK).
2.  **Request**: The user initiates an action. The ESP32 generates a random OTP.
3.  **Transmission**: The SIM800L sends the OTP to the registered mobile number.
4.  **Verification**: The user enters the received OTP on the keypad .
5.  **Action**: If the OTP matches, the relay toggles the power state and the buzzer sounds.

---

### 💻 Setup Instructions
1.  **Libraries Required**: 
    * `Keypad`
    * `LiquidCrystal_I2C`
    * `TinyGSM`
2.  **Configuration**: Update the `phone_number` in the source code with your target mobile number.
3.  **Power**: Ensure the SIM800L has a sufficient power supply (at least 2A peak) for GSM bursts.

---

### 🤝 Contributing
Feel free to fork this project and add features like **Firebase Data Logging** or a **Mobile App Interface**.

---

### 📜 License
This project is open-source under the MIT License.
