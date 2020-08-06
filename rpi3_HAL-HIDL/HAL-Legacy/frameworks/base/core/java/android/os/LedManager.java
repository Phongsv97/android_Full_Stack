package android.os;
 
import android.os.RemoteException;
import android.util.Log;
import android.os.ILedService;
import android.content.Context;
import android.content.pm.PackageManager;

 
public class LedManager
{
        private static final String TAG = "LedManager";
        private final ILedService mLedService;
        private Context mContext;
 
        public LedManager(Context context, ILedService service) {
                mContext = context;
                mLedService = service;
        }

        // public String get_status() {
        //         try {
	// 				Log.i("PHONGLT", "LedManager get_status start--- !");
	// 				return mLedService.get_status();
        //         } catch (RemoteException e) {
	// 				Log.e("PHONGLT", "LedManager get_status error--- !");
	// 				e.printStackTrace();
	// 				return -1;
        //         }
        // }
 
        public int config_led(String mString) {
                try {
					Log.i("PHONGLT", "LedManager config_led start--- !");
					return mLedService.config_led(mString);
                } catch (RemoteException e) {
					Log.e("PHONGLT", "LedManager config_led error--- !");
					e.printStackTrace();
					return -1;
                }
        }
}
