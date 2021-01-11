const String version_string = __TIMESTAMP__;

class CustomUpdater {
   public:
    CustomUpdater();
    void StorePersistentTime(unsigned long additionalOffset);
    void CheckForUpdate();
};