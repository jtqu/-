package edu.hhu.qujiatai;//����Ҫ�޸ĳ��Լ��İ���

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
		//ȫ��
		getWindow().setFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN,  WindowManager.LayoutParams.FLAG_FULLSCREEN);
		setContentView(R.layout.map);
		init();
		setListener();
	}

	private void init() {
		context = BaiduMapActivity.this;
		sp = context.getSharedPreferences("baidumap", Context.MODE_PRIVATE);
		mapView = (MapView) findViewById(R.id.mapView);
		//ȡ���Ŵ���С��
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
					Toast.makeText(context, "��ͨ��ͼ", Toast.LENGTH_LONG).show();
				}
				if(checkedId==R.id.satelliteRadioButton){
					baiduMap.setMapType(BaiduMap.MAP_TYPE_SATELLITE);
					Toast.makeText(context, "���ǵ�ͼ", Toast.LENGTH_LONG).show();
				}
			}
		});
		
		trafficCheckBox.setOnCheckedChangeListener(new CompoundButton.OnCheckedChangeListener() {
			@Override
			public void onCheckedChanged(CompoundButton compoundButton, boolean flag) {
				if(flag){
					//������ͨͼ
					baiduMap.setTrafficEnabled(true);
				}else{
					//�رս�ͨͼ
					baiduMap.setTrafficEnabled(false);
				}
			}
		});
	}
	
	//��Ӳ˵�
	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		//groupId,itemId,orderId,����
		menu.add(1,1,1,"��γ�ȶ�λ").setOnMenuItemClickListener(this);
		menu.add(2,2,2,"���ж�λ").setOnMenuItemClickListener(this);
		menu.add(3,3,3,"����������").setOnMenuItemClickListener(this);
		menu.add(4,4,4,"��ǰ�û���Ϣ").setOnMenuItemClickListener(this);
		menu.add(5,5,5,"�����Ļ").setOnMenuItemClickListener(this);
		menu.add(6,6,6,"�˳�").setOnMenuItemClickListener(this);
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
			builder.setTitle("��γ�ȶ�λ");
			builder.setView(locationView);
			final EditText longitudeEditText = (EditText) locationView.findViewById(R.id.longitudeEditText);
			final EditText latitudeEditText = (EditText) locationView.findViewById(R.id.latitudeEditText);
			builder.setPositiveButton("ȷ��",new DialogInterface.OnClickListener() {
				public void onClick(DialogInterface dialog, int which) {
					String longitudeString = longitudeEditText.getText().toString().trim();
					if(longitudeString.trim().length()==0){
						showToast(context, "���Ȳ���Ϊ��!");
						return;
					}
					String latitudeString = latitudeEditText.getText().toString().trim();
					if(latitudeString.trim().length()==0){
						showToast(context, "γ�Ȳ���Ϊ��!");
						return;
					}
					double longitude = Double.parseDouble(longitudeString);
					if(longitude<-180 || longitude>180){
						showToast(context, "���ȵķ�Χ��-180~180֮��!");
						return;
					}
					double latitude = Double.parseDouble(latitudeString);
					if(latitude<-90 || latitude>90){
						showToast(context, "γ�ȵķ�Χ��-90~90֮��!");
						return;
					}
					// ����Maker�����
					pointOverlay(baiduMap,longitude,latitude);
					// ����ͼ�ƶ���ȥ
					toNewAddress(baiduMap,longitude,latitude);
				}
			});
			builder.setNegativeButton("ȡ��", null);
			builder.create();
			builder.show();
			break;
		case 2:
			
			break;
		case 3:

			break;
		case 4:
			
			break;
		case 5://�����Ļ
			baiduMap.clear();
			break;
		case 6:
			builder.setTitle("�˳�����");
			builder.setMessage("��ȷ���˳���");
			builder.setPositiveButton("ȷ��", new DialogInterface.OnClickListener() {
				public void onClick(DialogInterface dialog, int which) {
					BaiduMapActivity.this.finish();
				}
			});
			builder.setNegativeButton("ȡ��", null);
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
	 * ����ͼ�����˵��ƶ���ָ����
	 * @param baiduMap �ٶȵ�ͼ����
	 * @param longitude ����
	 * @param latitude γ��
	 */
	private void toNewAddress(BaiduMap baiduMap,double longitude,double latitude){
		//�趨���ĵ�����
		LatLng cenpt = new LatLng(latitude,longitude);
		//�����ͼ״̬
		MapStatus mapStatus = new MapStatus.Builder().target(cenpt).build();
		//����MapStatusUpdate�����Ա�������ͼ״̬��Ҫ�����ı仯
		MapStatusUpdate mapStatusUpdate = MapStatusUpdateFactory.newMapStatus(mapStatus);
		//�ı��ͼ״̬
		baiduMap.setMapStatus(mapStatusUpdate);
	}
	
	/**
	 * ���Ƶ��ǣ������µĵ�����ӵ���ͼ��
	 * @param baiduMap �ٶȵ�ͼ����
	 * @param longitude ����
	 * @param latitude γ��
	 */
	private void pointOverlay(BaiduMap baiduMap,double longitude,double latitude){
		//����Maker�����
		LatLng point = new LatLng(latitude,longitude);
		//����Markerͼ��
		BitmapDescriptor bitmap = BitmapDescriptorFactory.fromResource(R.drawable.mark);
		//����MarkerOption�������ڵ�ͼ�����Marker
		OverlayOptions option = new MarkerOptions().position(point).icon(bitmap);
		//�ڵ�ͼ�����Marker������ʾ
		baiduMap.addOverlay(option);
	}
	
	public boolean onKeyDown(int keyCode, KeyEvent event) {
		// �Ƿ񴥷�����Ϊback��
		if (keyCode == KeyEvent.KEYCODE_BACK) {
			exist();
			return true;
		} else {
			return super.onKeyDown(keyCode, event);
		}
	}
	
	//�˳�
	private void exist(){
		AlertDialog.Builder builder = new AlertDialog.Builder(BaiduMapActivity.this);
		builder.setIcon(R.drawable.ic_launcher);
		builder.setTitle("�˳�����");
		builder.setMessage("��ȷ���˳���");
		builder.setPositiveButton("ȷ��", new DialogInterface.OnClickListener() {
			public void onClick(DialogInterface dialog, int which) {
				BaiduMapActivity.this.finish();
			}
		});
		builder.setNegativeButton("ȡ��", null);
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
