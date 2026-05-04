# 🛡️ ESP32 Based Lineman Security System

An advanced IoT-based security solution designed for electrical linemen to prevent unauthorized access to high-voltage lines or industrial machinery. The system utilizes **Two-Factor Authentication (2FA)** via OTP sent over GSM to ensure maximum safety during maintenance.

---

### 🚀 Key Features
* **OTP-Based Authentication**: Generates a unique 4-digit One-Time Password for every access request [cite: 1].
* **GSM Connectivity**: Uses SIM800L to send OTPs directly to the supervisor's or lineman's mobile device [cite: 1].
* **Local UI & Feedback**: 16x2 LCD for status messages and a buzzer for audible confirmation/warnings [cite: 1].
* **Secure Control**: Industrial-grade relay module to manage power state (Lock/Unlock) [cite: 1].
* **Robust Input**: 4x4 Matrix Keypad for manual OTP entry [cite: 1].

---

### 🛠️ Hardware Components
| Component | Description |
| :--- | :--- |
| **ESP32** | The brain of the system, handling logic and communication [cite: 1]. |
| **SIM800L GSM Module** | Handles SMS transmission and reception [cite: 1]. |
| **16x2 LCD (I2C)** | Displays system states (e.g., "SYSTEM LOCKED", "ENTER OTP") [cite: 1]. |
| **4x4 Keypad** | Used for user input of the OTP [cite: 1]. |
| **5V Relay Module** | Controls the electrical load/line connection [cite: 1]. |
| **Buzzer** | Provides audio alerts for success or failure [cite: 1]. |
| **Li-ion Battery** | Power source for portability and reliability [cite: 1]. |

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
1.  **System Idle**: The LCD displays the current status (LOCK/UNLOCK) [cite: 1].
2.  **Request**: The user initiates an action. The ESP32 generates a random OTP [cite: 1].
3.  **Transmission**: The SIM800L sends the OTP to the registered mobile number [cite: 1].
4.  **Verification**: The user enters the received OTP on the keypad [cite: 1].
5.  **Action**: If the OTP matches, the relay toggles the power state and the buzzer sounds [cite: 1].

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
