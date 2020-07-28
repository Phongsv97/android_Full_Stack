package android.os;
import android.os.ILedService;

public class LedManager
{
	public void init(String name)
	{
		mService.init(name);
	}

	public void config(int val)
	{
		mService.config(val);
	}

	public LedManager(ILedService service)
	{
		mService = service;
	}

	ILedService mService;
}
