#include "get_time.h"


// ================= NTP =================
const char* NTP_SERVER = "asia.pool.ntp.org";

// Việt Nam: UTC+7
const long GMT_OFFSET_SEC = 7 * 3600;

//const long GMT_OFFSET_SEC = 0;
const int DAYLIGHT_OFFSET_SEC = 0;




tm timeinfo;









bool get_time_init()
{
    Serial.println("[NTP SERVER TIME] Initializing time synchronization...");
    // Đồng bộ thời gian từ NTP
    configTime(
        GMT_OFFSET_SEC,
        DAYLIGHT_OFFSET_SEC,
        NTP_SERVER,
        "time.google.com"
    );

    Serial.print("Syncing time");
    time_t now = time(nullptr);
    while (now < 1700000000) {   // ~ tháng 11/2023, tức là đã sync
        delay(200);
        Serial.print(".");
        now = time(nullptr);
    }
    Serial.println();
    Serial.println(ctime(&now));

    while (!getLocalTime(&timeinfo))
    {
        Serial.println("[NTP SERVER TIME] Waiting for time synchronization...");
        vTaskDelay(pdMS_TO_TICKS(100));
    }
    Serial.println();
    Serial.println("[NTP SERVER TIME]Time from NTP Server synchronized successfully!");
    return true;
}













void get_time_HHMMSS()
{

    if (getLocalTime(&timeinfo))
    {
        Serial.printf(
            "%02d:%02d:%02d\n",

            timeinfo.tm_hour,
            timeinfo.tm_min,
            timeinfo.tm_sec
        );
    }

    else
    {
        Serial.println("Failed to obtain time from NTP server!");
        return;
    }
}



String get_time_yyyymmdd_hhmmss() {

    if (!getLocalTime(&timeinfo)) return "";

    char buffer[20];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", &timeinfo);
    Serial.println(buffer);
    return String(buffer);

}