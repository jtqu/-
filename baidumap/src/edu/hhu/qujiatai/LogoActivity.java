package edu.hhu.qujiatai;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.os.Handler;
import android.view.Menu;
import android.view.MenuItem;

public class LogoActivity extends Activity {

	private Handler handler = new Handler(){
		public void handleMessage(android.os.Message msg){
			if(msg.what==1){
				Intent intent = new Intent(LogoActivity.this,LoginActivity.class);
				//页面跳转
				startActivity(intent);
				//关闭当前页面
				finish();
			}
			
		}
	};
	
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.logo);
		
		//实现3s后跳转到login页面
		handler.sendEmptyMessageDelayed(1, 3000);
	}
	
}
