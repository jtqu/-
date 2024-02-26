package edu.hhu.qujiatai;//这里要修改成自己的包名

import java.util.HashMap;
import java.util.Map;

import org.json.JSONException;
import org.json.JSONObject;

import com.baidu.mapapi.map.BaiduMap;
import com.baidu.mapapi.map.BitmapDescriptor;
import com.baidu.mapapi.map.BitmapDescriptorFactory;
import com.baidu.mapapi.map.MapStatus;
import com.baidu.mapapi.map.MapStatusUpdate;
import com.baidu.mapapi.map.MapStatusUpdateFactory;
import com.baidu.mapapi.map.MapView;
import com.baidu.mapapi.map.MarkerOptions;
import com.baidu.mapapi.map.OverlayOptions;
import com.baidu.mapapi.model.LatLng;
import com.baidu.mapapi.utils.DistanceUtil;

import android.app.Activity;
import android.app.AlertDialog;
import android.content.Context;
import android.content.DialogInterface;
import android.content.SharedPreferences;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.view.KeyEvent;
import android.view.Menu;
import android.view.MenuItem;
import android.view.MenuItem.OnMenuItemClickListener;
import android.view.View;
import android.view.WindowManager;
import android.widget.CheckBox;
import android.widget.CompoundButton;
import android.widget.EditText;
import android.widget.RadioButton;
import android.widget.RadioGroup;
import android.widget.Toast;

public class BaiduMapActivity extends Activity implements OnMenuItemClickListener{

	private Context context;
	private SharedPreferences sp;
	private MapView mapView;
	private BaiduMap baiduMap;
	private RadioGroup maptypeRadioGroup;
	private CheckBox trafficCheckBox;
	private Handler handler;

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		//全屏
		getWindow().setFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN,  WindowManager.LayoutParams.FLAG_FULLSCREEN);
		setContentView(R.layout.map);
		init();
		setListener();
	}

	private void init() {
		context = BaiduMapActivity.this;
		sp = context.getSharedPreferences("baidumap", Context.MODE_PRIVATE);
		mapView = (MapView) findViewById(R.id.mapView);
		//取消放大缩小键
		mapView.showZoomControls(true);
		baiduMap = mapView.getMap();
		toNewAddress(baiduMap,118.78,32.07);
		maptypeRadioGroup = (RadioGroup) findViewById(R.id.maptypeRadioGroup);
		trafficCheckBox = (CheckBox) findViewById(R.id.trafficCheckBox);
		handler = new Handler(){
			@Override
			public void handleMessage(final Message msg) {
				switch(msg.what){
				case 1:
					showToast(context, msg.obj.toString());
					break;
				}
			}
		};
	}

	private void setListener() {
		maptypeRadioGroup.setOnCheckedChangeListener(new RadioGroup.OnCheckedChangeListener() {
			@Override
			public void onCheckedChanged(RadioGroup group, int checkedId) {
				if(checkedId==R.id.normalRadioButton){
					baiduMap.setMapType(BaiduMap.MAP_TYPE_NORMAL);
					Toast.makeText(context, "普通地图", Toast.LENGTH_LONG).show();
				}
				if(checkedId==R.id.satelliteRadioButton){
					baiduMap.setMapType(BaiduMap.MAP_TYPE_SATELLITE);
					Toast.makeText(context, "卫星地图", Toast.LENGTH_LONG).show();
				}
			}
		});
		
		trafficCheckBox.setOnCheckedChangeListener(new CompoundButton.OnCheckedChangeListener() {
			@Override
			public void onCheckedChanged(CompoundButton compoundButton, boolean flag) {
				if(flag){
					//开启交通图
					baiduMap.setTrafficEnabled(true);
				}else{
					//关闭交通图
					baiduMap.setTrafficEnabled(false);
				}
			}
		});
	}
	
	//添加菜单
	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		//groupId,itemId,orderId,名称
		menu.add(1,1,1,"经纬度定位").setOnMenuItemClickListener(this);
		menu.add(2,2,2,"城市定位").setOnMenuItemClickListener(this);
		menu.add(3,3,3,"公里数计算").setOnMenuItemClickListener(this);
		menu.add(4,4,4,"当前用户信息").setOnMenuItemClickListener(this);
		menu.add(5,5,5,"清除屏幕").setOnMenuItemClickListener(this);
		menu.add(6,6,6,"退出").setOnMenuItemClickListener(this);
		return super.onCreateOptionsMenu(menu);
	}
	
	@Override
	public boolean onMenuItemClick(MenuItem item) {
		int itemId = item.getItemId();
		AlertDialog.Builder builder = new AlertDialog.Builder(BaiduMapActivity.this);
		builder.setIcon(R.drawable.ic_launcher);
		switch(itemId){
		case 1:
			final View locationView = View.inflate(BaiduMapActivity.this,R.layout.dialog_location, null);
			builder.setTitle("经纬度定位");
			builder.setView(locationView);
			final EditText longitudeEditText = (EditText) locationView.findViewById(R.id.longitudeEditText);
			final EditText latitudeEditText = (EditText) locationView.findViewById(R.id.latitudeEditText);
			builder.setPositiveButton("确定",new DialogInterface.OnClickListener() {
				public void onClick(DialogInterface dialog, int which) {
					String longitudeString = longitudeEditText.getText().toString().trim();
					if(longitudeString.trim().length()==0){
						showToast(context, "经度不能为空!");
						return;
					}
					String latitudeString = latitudeEditText.getText().toString().trim();
					if(latitudeString.trim().length()==0){
						showToast(context, "纬度不能为空!");
						return;
					}
					double longitude = Double.parseDouble(longitudeString);
					if(longitude<-180 || longitude>180){
						showToast(context, "经度的范围在-180~180之间!");
						return;
					}
					double latitude = Double.parseDouble(latitudeString);
					if(latitude<-90 || latitude>90){
						showToast(context, "纬度的范围在-90~90之间!");
						return;
					}
					// 定义Maker坐标点
					pointOverlay(baiduMap,longitude,latitude);
					// 将地图移动过去
					toNewAddress(baiduMap,longitude,latitude);
				}
			});
			builder.setNegativeButton("取消", null);
			builder.create();
			builder.show();
			break;
		case 2:
			
			break;
		case 3:

			break;
		case 4:
			
			break;
		case 5://清除屏幕
			baiduMap.clear();
			break;
		case 6:
			builder.setTitle("退出提醒");
			builder.setMessage("你确认退出吗？");
			builder.setPositiveButton("确定", new DialogInterface.OnClickListener() {
				public void onClick(DialogInterface dialog, int which) {
					BaiduMapActivity.this.finish();
				}
			});
			builder.setNegativeButton("取消", null);
			builder.create();
			builder.show();
			break;
		default:
			break;
		}
		return true;
	}
	
	private void showToast(Context context,String content){
		Toast.makeText(context, content, Toast.LENGTH_SHORT).show();
	}
	
	/**
	 * 将地图的中兴点移动到指定点
	 * @param baiduMap 百度地图对象
	 * @param longitude 经度
	 * @param latitude 纬度
	 */
	private void toNewAddress(BaiduMap baiduMap,double longitude,double latitude){
		//设定中心点坐标
		LatLng cenpt = new LatLng(latitude,longitude);
		//定义地图状态
		MapStatus mapStatus = new MapStatus.Builder().target(cenpt).build();
		//定义MapStatusUpdate对象，以便描述地图状态将要发生的变化
		MapStatusUpdate mapStatusUpdate = MapStatusUpdateFactory.newMapStatus(mapStatus);
		//改变地图状态
		baiduMap.setMapStatus(mapStatusUpdate);
	}
	
	/**
	 * 绘制点标记，并将新的点标记添加到地图中
	 * @param baiduMap 百度地图对象
	 * @param longitude 经度
	 * @param latitude 纬度
	 */
	private void pointOverlay(BaiduMap baiduMap,double longitude,double latitude){
		//定义Maker坐标点
		LatLng point = new LatLng(latitude,longitude);
		//构建Marker图标
		BitmapDescriptor bitmap = BitmapDescriptorFactory.fromResource(R.drawable.mark);
		//构建MarkerOption，用于在地图上添加Marker
		OverlayOptions option = new MarkerOptions().position(point).icon(bitmap);
		//在地图上添加Marker，并显示
		baiduMap.addOverlay(option);
	}
	
	public boolean onKeyDown(int keyCode, KeyEvent event) {
		// 是否触发按键为back键
		if (keyCode == KeyEvent.KEYCODE_BACK) {
			exist();
			return true;
		} else {
			return super.onKeyDown(keyCode, event);
		}
	}
	
	//退出
	private void exist(){
		AlertDialog.Builder builder = new AlertDialog.Builder(BaiduMapActivity.this);
		builder.setIcon(R.drawable.ic_launcher);
		builder.setTitle("退出提醒");
		builder.setMessage("你确认退出吗？");
		builder.setPositiveButton("确定", new DialogInterface.OnClickListener() {
			public void onClick(DialogInterface dialog, int which) {
				BaiduMapActivity.this.finish();
			}
		});
		builder.setNegativeButton("取消", null);
		builder.create();
		builder.show();
	}

	@Override
	protected void onResume() {
		super.onResume();
		mapView.onResume();
	}

	@Override
	protected void onPause() {
		super.onPause();
		mapView.onPause();
	}

	@Override
	protected void onDestroy() {
		super.onDestroy();
		mapView.onDestroy();
	}

}
