const String version_string = __DATE__ " " __TIME__;

class CustomUpdater {
   public:
    CustomUpdater();
    void StorePersistentTime(unsigned long additionalOffset);
    void CheckForUpdate();
};