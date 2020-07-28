package android.os;
/**
* {@hide}
*/
interface ILedService {
	void init(String name);
	void get_status();
}
