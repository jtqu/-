package edu.hhu.qujiatai;

import java.text.SimpleDateFormat;
import java.util.Calendar;
import java.util.Date;
import java.util.regex.Pattern;

import android.app.Activity;
import android.app.AlertDialog;
import android.app.DatePickerDialog;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.DatePicker;
import android.widget.EditText;
import android.widget.RadioButton;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.Spinner;
import android.widget.TextView;
import android.widget.Toast;
import android.content.Context;
import android.content.DialogInterface;
import android.content.Intent;
import android.content.SharedPreferences;
import android.content.SharedPreferences.Editor;

public class RegisterActivity extends Activity {
	
	private Context context;
	//birthday
	private EditText birthdayEditText;
	private SimpleDateFormat sdf;
	private int year;
	private int monthOfYear;
	private int dayOfMonth;
	private TextView middleLineTextView;	
	private String[] interestArray;
	private boolean[] interestChoseArray;
	private EditText hobbyEditText;
	private Spinner provinceSpinner;
	private Spinner citySpinner;
	private int provinceIndex;
	private int cityIndex;
	
	// 负责简单数据的获取
		private SharedPreferences sp;
		// 简单数据的存储
		private Editor editor;
		// 分隔符
		private final String SPL = ":_:";
	
		
		private EditText nameEditText;
		private EditText accountEditText;
		private EditText password1EditText;
		private EditText password2EditText;
		private RadioButton maleRadioButton;
		private EditText PhoneNumberEditText;
		private EditText emailEditText;
		private EditText assessmentEditText;
		
	private Button registerButton;
	private Button cancelButton;
	
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		// TODO Auto-generated method stub
		super.onCreate(savedInstanceState);
		setContentView(R.layout.register);
		Init();
		addAction();
	}
	
	private void Init(){
		
		sp = getSharedPreferences("baidumap", Context.MODE_PRIVATE);
		editor = sp.edit();
		
		accountEditText=(EditText) findViewById(R.id.accountEditText);
		
		
		
		registerButton = (Button) findViewById(R.id.registerButton);
		cancelButton = (Button) findViewById(R.id.cancelButton);
		nameEditText = (EditText) findViewById(R.id.nameEditText);
		maleRadioButton = (RadioButton) findViewById(R.id.maleRadioButton);
		password1EditText = (EditText) findViewById(R.id.password1EditText);
		password2EditText = (EditText) findViewById(R.id.password2EditText);
		PhoneNumberEditText = (EditText) findViewById(R.id.PhoneNumberEditText);
		emailEditText = (EditText) findViewById(R.id.emailEditText);
		assessmentEditText = (EditText) findViewById(R.id.assessmentEditText);
		
		
		birthdayEditText = (EditText) findViewById(R.id.birthEditText);
		sdf = new SimpleDateFormat("yyyy-MM-dd");
		context = this;
		Calendar calendar = Calendar.getInstance();
		year = calendar.get(Calendar.YEAR);
		monthOfYear = calendar.get(Calendar.MONTH);
		dayOfMonth = calendar.get(Calendar.DAY_OF_MONTH);
		
		interestArray = new String[] { "打篮球", "踢足球", "看电影", "打游戏", "学习", "爬山", "旅游", "打扑克" };
		interestChoseArray = new boolean[8];
		hobbyEditText = (EditText) findViewById(R.id.hobbyEditText);
		
		provinceSpinner = (Spinner) findViewById(R.id.provinceSpinner);
		citySpinner = (Spinner) findViewById(R.id.citySpinner);
		middleLineTextView = (TextView) findViewById(R.id.middleLineTextView);
		
		// 填充省下拉的数据
				ArrayAdapter<String> provinceAdapter = new ArrayAdapter<String>(context, android.R.layout.simple_spinner_item,
						ProvinceCityUtil.PROVINCE_ARRAY);
				provinceAdapter.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item);
				provinceSpinner.setAdapter(provinceAdapter);
		
				
	}
	
	private void addAction() {
		// 添加生日输入控件的单击事件
		birthdayEditText.setOnClickListener(new View.OnClickListener() {	
			@Override
			public void onClick(View view) {

				DatePickerDialog datePickerDialog = new DatePickerDialog(context,
						new DatePickerDialog.OnDateSetListener() {

							@Override
							public void onDateSet(DatePicker datePicker, int y, int m, int d) {

								Calendar c = Calendar.getInstance();
								Date date = new Date(System.currentTimeMillis());
								c.set(y, m, d);
								String dateString = sdf.format(c.getTime());
								if (c.getTime().before(date))
									dateString = sdf.format(c.getTime());
								else if (c.getTime().after(date)){
									Toast.makeText(RegisterActivity.this, "日期错误", Toast.LENGTH_LONG).show();
									return;
								}
								birthdayEditText.setText(y + "-" + (m + 1) + "-" + d);
                               
							}
						}, year - 18, monthOfYear, dayOfMonth);
				datePickerDialog.show();
			}
		});
		
		//兴趣爱好
		hobbyEditText.setOnClickListener(new View.OnClickListener() {
			// 添加兴趣输入控件的单击事件
			@Override
			public void onClick(View view) {
				/*
				 * 设置该对话框的一些信息  设置对话框的消息内容  为"确定"和"取消"按钮绑定事件监听  创建对话框  显示对话框
				 */
				// 1.根据上下文对象创建一个简单对话框的创建器
				AlertDialog.Builder builder = new AlertDialog.Builder(context);
				// 2.设置对话框的一些信息
				builder.setIcon(R.drawable.ic_launcher);
				builder.setTitle("请选择你的兴趣:");
				// 3.设置对话框的消息内容
				builder.setMultiChoiceItems(interestArray, interestChoseArray,
						new DialogInterface.OnMultiChoiceClickListener() {
							@Override
							public void onClick(DialogInterface view, int index, boolean flag) {
								interestChoseArray[index] = flag;
							}
						});

				// 4.为"确定"和"取消"按钮绑定事件监听
				builder.setPositiveButton("确定", new DialogInterface.OnClickListener() {

					@Override
					public void onClick(DialogInterface arg0, int arg1) {
						StringBuilder sb = new StringBuilder();
						for (int i = 0; i < interestArray.length; i++) {
							if (interestChoseArray[i]) {
								sb.append(interestArray[i]).append(",");
							}
						}
						String interest = sb.toString();
						hobbyEditText.setText(interest.substring(0, interest.length() - 1));
					}
				});
				builder.setNegativeButton("取消", null);
				// 5.创建对话框
				//builder.create();
				// 6.显示对话框
				builder.show();
			}
		});
		
		
		
		
		//籍贯省
		provinceSpinner.setOnItemSelectedListener(new AdapterView.OnItemSelectedListener() {
			@Override
			public void onItemSelected(AdapterView<?> av, View view, int index, long ar3) {
				provinceIndex = index;
				if (index == 0 || index == 1 || index == 2 || index == 3 || index == 32 || index == 31) {
					middleLineTextView.setVisibility(View.INVISIBLE);
					citySpinner.setVisibility(View.INVISIBLE);
					cityIndex = -1;
				} else {
					middleLineTextView.setVisibility(View.VISIBLE);
					citySpinner.setVisibility(View.VISIBLE);
					cityIndex = 0;
					// 填充市下拉的数据
					ArrayAdapter<String> cityAdapter = new ArrayAdapter<String>(context,
							android.R.layout.simple_spinner_item, ProvinceCityUtil.CITY_ARRAY[provinceIndex]);
					cityAdapter.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item);
					citySpinner.setAdapter(cityAdapter);

				}

			}
			@Override
			public void onNothingSelected(AdapterView<?> arg0) {
				// TODO Auto-generated method stub

			}
		});
			

			//籍贯市
			citySpinner.setOnItemSelectedListener(new AdapterView.OnItemSelectedListener() {

				@Override
				public void onItemSelected(AdapterView<?> av, View view, int index, long ar3) {
					cityIndex = index;

				}

				@Override
				public void onNothingSelected(AdapterView<?> arg0) {
					// TODO Auto-generated method stub

				}
			});
			
			registerButton.setOnClickListener(new View.OnClickListener() {

				@Override
				public void onClick(View view) {
					// 1.获取用户输入或者选择的信息
					String name = nameEditText.getText().toString().trim();
					String acccount = accountEditText.getText().toString().trim();
					String password1 = password1EditText.getText().toString().trim();
					String password2 = password2EditText.getText().toString().trim();
					String phone = PhoneNumberEditText.getText().toString().trim();
					String gender = maleRadioButton.isChecked() ? "男" : "女";
					String email = emailEditText.getText().toString().trim();
					String interest = hobbyEditText.getText().toString().trim();
					String birthday = birthdayEditText.getText().toString().trim();
					String birthplace = ProvinceCityUtil.PROVINCE_ARRAY[provinceIndex];
					if (cityIndex >= 0) {
						birthplace = birthplace + "-" + ProvinceCityUtil.CITY_ARRAY[provinceIndex][cityIndex];
					}
					String assessment = assessmentEditText.getText().toString().trim();
					// 2.做相关的数据验证
					// 2.1注册页面已存在账号的验证
					String info = sp.getString(acccount, "");
					if (!info.equals("")) {
						Toast.makeText(context, acccount + "已经被注册！", Toast.LENGTH_SHORT).show();
						return;
					}
					// 2.2注册页面重复密码的验证
					String pass1 = sp.getString(password1, "");
					String pass2 = sp.getString(password2, "");				
					if (pass1!=pass2) {
						Toast.makeText(context, "前后密码不一致！", Toast.LENGTH_SHORT).show();
						return;
					}
					// 2.3注册页面邮箱格式的验证
					String emailget = "\\w+([-+.]\\w+)*@\\w+([-.]\\w+)*\\.\\w+([-.]\\w+)*";
					if (!Pattern.matches(emailget, email)){
						Toast.makeText(context, "邮箱格式不符合规定!", Toast.LENGTH_SHORT).show();
						return;
					}			
					// 2.4注册页面手机格式的验证
					String regex = "^((13[0-9])|(14[5|7])|(15([0-3]|[5-9]))|(18[0,5-9]))\\d{8}$";
					if (!Pattern.matches(regex, phone)) {
						Toast.makeText(context, "手机号码不符合规定!", Toast.LENGTH_SHORT).show();
						return;
					}
					// 3.存储数据
					StringBuilder sb = new StringBuilder();
					sb.append(password1).append(SPL);
					sb.append("0_0").append(SPL);
					sb.append(name).append(SPL);
					sb.append(gender).append(SPL);
					sb.append(phone).append(SPL);
					sb.append(email).append(SPL);
					sb.append(interest).append(SPL);
					sb.append(birthday).append(SPL);
					sb.append(birthplace).append(SPL);
					sb.append(assessment).append(SPL);
					String userInformation = sb.toString();
					Log.i("用户信息", userInformation);
					editor.putString(acccount, sb.toString());
					editor.commit();
					Toast.makeText(context, "注册成功！", Toast.LENGTH_SHORT).show();
					Intent intent = new Intent(context, LoginActivity.class);
					startActivity(intent);
					finish();
				}
			});
			
			// 取消按钮的单击事件
			cancelButton.setOnClickListener(new View.OnClickListener() {

				@Override
				public void onClick(View arg0) {
					Intent intent = new Intent(context, LoginActivity.class);
					startActivity(intent);
					finish();

				}
			});
			
	}
}
