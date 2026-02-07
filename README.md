# Giới thiệu
HLK-LD2420-v2.0 là module cảm biến hiện diện người (Human Presence) dựa trên kiến trúc radar 1T1R. Khác với cảm biến hồng ngoại (PIR) truyền thống, Radar mmWave có thể phát hiện người ngay cả khi đứng yên nhờ nhận diện các cử động nhỏ như nhịp thở.

## Thông số kỹ thuật
*   **Băng tần:** 24GHz - 24.25GHz.
*   **Điện áp hoạt động:** 3.3V DC (Định mức an toàn cho ESP32).
*   **Dòng tiêu thụ:** ≈ 50mA.
*   **Khoảng cách phát hiện:** Lên đến 8m (có thể điều chỉnh từng vùng 0.75m).
*   **Giao tiếp:** UART (Mặc định cấu hình trong code là 115200 bps).
*   **Ngõ ra phụ:** Chân OUT (OT2) xuất mức logic (3.3V khi có người).

---

# Sơ đồ kết nối (Wiring Diagram)

Hệ thống sử dụng giao tiếp Serial2 của ESP32 để đọc dữ liệu thô từ Radar.

| Chân LD2420-v2 | Chân ESP32 | Chức năng |
| :--- | :--- | :--- |
| **3V3** | 3.3V | Cấp nguồn 3.3V |
| **GND** | GND | Tiếp địa (GND) |
| **OT1 (TX)** | GPIO 4 | Truyền dữ liệu UART sang ESP32 (RX_PIN) |
| **RX** | GPIO 5 | Nhận lệnh UART từ ESP32 (TX_PIN) |
| **OT2** | [NC] | Output tín hiệu Logic (Không dùng trong code này) |

---

# Tính năng mã nguồn
Mã nguồn được phát triển với tư duy hệ thống quản lý thông minh, bao gồm:
1.  **Lọc khoảng cách:** Chỉ kích hoạt thiết bị khi đối tượng cách cảm biến dưới **100cm**.
2.  **Cơ chế Override (Điều khiển người dùng):** 
    *   Gửi lệnh `SLEEP` qua Serial Monitor để tạm dừng hệ thống.
    *   Gửi lệnh `WAKE` để kích hoạt lại hệ thống.
3.  **Xử lý Non-blocking:** Sử dụng `millis()` để quản lý thời gian, đảm bảo ESP32 luôn sẵn sàng nhận lệnh từ người dùng.
