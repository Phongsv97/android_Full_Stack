package android.os;
 
/** {@hide} */
interface IVolbtnService
{   
    String get_status();
    void config_led(String mString);
}