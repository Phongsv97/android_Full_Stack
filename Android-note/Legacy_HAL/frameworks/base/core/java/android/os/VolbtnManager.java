package android.os;
 
import android.os.RemoteException;
import android.util.Log;
import android.os.IVolbtnService;
import android.content.Context;
import android.content.pm.PackageManager;
/**
 * Wrapper class for VolumeDownService;
 */
 
public class VolbtnManager
{
        private static final String TAG = "VolbtnManager";
        private final IVolbtnService mVolumeDownService;
        private Context mContext;
 
        public VolbtnManager(Context context, IVolbtnService service) {
                mContext = context;
                mVolumeDownService = service;
        }
 
        public int volumnDownStatus() {
                try{
					Log.e("pptv", "VolbtnManager  start--- !");
					return mVolumeDownService.read_btn_status();
			//      Log.e("pptv", "VolbtnManager  ledCtrl--- !");
                } catch (RemoteException e) {
					Log.e("pptv", "VolbtnManager  error--- !");
					e.printStackTrace();
					return -1;
                }
        }
}
