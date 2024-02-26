package edu.hhu.qujiatai;

import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.content.SharedPreferences;
import android.content.SharedPreferences.Editor;
import android.os.Bundle;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.Button;
import android.widget.CheckBox;
import android.widget.CompoundButton;
import android.widget.EditText;
import android.widget.Toast;

public class LoginActivity extends Activity {

	/*
	 * 1.在布局文件中给需要在Java代码中操作的控件取唯一的id值 2.在Activity类中声明和控件对应的成员变量
	 * 3.将布局文件中的控件和Activity中的成员变量进行绑定
	 */

	private EditText accountEditText;
	private EditText passwordEditText;
	private CheckBox rememberAccountCheckBox;
	private CheckBox rememberPasswordCheckBox;
	private Button loginButton;
	private Button registerButton;
	private final String SPL = ":_:";
	private SharedPreferences sp;
	private Editor editor;

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.login);
		init();
		addAction();
	}

	// 初始化
	private void init() {
		accountEditText = (EditText) findViewById(R.id.accountEditText);
		passwordEditText = (EditText) findViewById(R.id.passwordEditText);
		rememberAccountCheckBox = (CheckBox) findViewById(R.id.rememberAccountCheckBox);
		rememberPasswordCheckBox = (CheckBox) findViewById(R.id.rememberPasswordCheckBox);
		loginButton = (Button) findViewById(R.id.loginButton);
		registerButton = (Button) findViewById(R.id.registerButton);

		sp = getSharedPreferences("baidumap", Context.MODE_PRIVATE);
		editor = sp.edit();

		String currentAccount = sp.getString("curruntAccount", "");
		if (!currentAccount.equals("")) {
			String userInformation = sp.getString(currentAccount, "");
			String[] userInformationArray = userInformation.split(SPL);
			String rememberAccount = userInformationArray[1].split("_")[0];
			String rememberPassword = userInformationArray[1].split("_")[1];
			if (rememberAccount.equals("1")) {
				accountEditText.setText(currentAccount);
				rememberAccountCheckBox.setChecked(true);
			}
			if (rememberPassword.equals("1")) {
				passwordEditText.setText(userInformationArray[0]);
				rememberPasswordCheckBox.setChecked(true);
			}
		} else {
			accountEditText.setText("");
			rememberAccountCheckBox.setChecked(false);
			passwordEditText.setText("");
			rememberPasswordCheckBox.setChecked(true);
		}

	}

	// 添加事件监听
	private void addAction() {

		// 记住账号复选框添加单机监听事件
		rememberAccountCheckBox.setOnCheckedChangeListener(new CompoundButton.OnCheckedChangeListener() {
			@Override
			public void onCheckedChanged(CompoundButton compoundButton, boolean flag) {
				if (flag) {
				} else {
					rememberPasswordCheckBox.setChecked(false);
				}
			}

		});
		// 记住密码复选框添加单机监听事件
		rememberPasswordCheckBox.setOnCheckedChangeListener(new CompoundButton.OnCheckedChangeListener() {
			@Override
			public void onCheckedChanged(CompoundButton compoundButton, boolean flag) {
				if (flag) {
					rememberAccountCheckBox.setChecked(true);
				} else {
				}
			}

		});

		loginButton.setOnClickListener(new View.OnClickListener() {
			@Override
			public void onClick(View argo) {
				String account = accountEditText.getText().toString();
				String password = passwordEditText.getText().toString();
				String userInformation = sp.getString(account, "");
				if (userInformation.equals("")) {
					Toast.makeText(LoginActivity.this, account + "账号不存在！", Toast.LENGTH_LONG).show();
					return;
				}
				String[] userInformationArray = userInformation.split(SPL);
				if (!password.equals(userInformationArray[0])) {
					Toast.makeText(LoginActivity.this, "密码错误！", Toast.LENGTH_LONG).show();
					return;
				}

				Toast.makeText(LoginActivity.this, "登录成功!", 3000).show();
				Intent intent = new Intent(LoginActivity.this, BaiduMapActivity.class);
				startActivity(intent);
				finish();
			}
		});

		/*
		 * // 添加登录按钮的业务逻辑 loginButton.setOnClickListener(new
		 * View.OnClickListener() {
		 * 
		 * @Override public void onClick(View view) { // 1.获取用户所输入的账号和密码的值
		 * String account = accountEditText.getText().toString().trim(); String
		 * password = passwordEditText.getText().toString().trim(); //
		 * 2.进行账号和密码的比较（demo）
		 * 
		 * if (account.equals("qujiatai") && password.equals("123456")) {
		 * Toast.makeText(LoginActivity.this, "登陆成功！\n进入地图主页面",
		 * Toast.LENGTH_LONG).show(); } else {
		 * Toast.makeText(LoginActivity.this, "账号或密码错误！",
		 * Toast.LENGTH_LONG).show(); }
		 * 
		 * // 2.进行账号和密码的比较（真实数据） String userInformation = sp.getString(account,
		 * ""); if (userInformation.equals("")) {
		 * Toast.makeText(LoginActivity.this, account + "账号不存在！",
		 * Toast.LENGTH_LONG).show(); return; } String[] userInformationArray =
		 * userInformation.split(SPL);
		 * 
		 * if (!password.equals(userInformationArray[0])) {
		 * Toast.makeText(LoginActivity.this, "密码错误！",
		 * Toast.LENGTH_LONG).show(); return; } //
		 * 将最新的记住账号和记住密码的状态更新到baidumap.xml文件中 String rememberStatus = ""; if
		 * (!rememberAccountCheckBox.isChecked() &&
		 * !rememberPasswordCheckBox.isChecked()) { rememberStatus = "0_0"; } if
		 * (rememberAccountCheckBox.isChecked() &&
		 * rememberPasswordCheckBox.isChecked()) { rememberStatus = "1_1"; } if
		 * (rememberAccountCheckBox.isChecked() &&
		 * !rememberPasswordCheckBox.isChecked()) { rememberStatus = "1_0"; }
		 * userInformation = userInformation.replace(userInformationArray[1],
		 * rememberStatus);
		 * 
		 * // 3.将当前登录的账号保存起来 editor.putString("currentAccount", account);
		 * editor.putString("userInformationArray[1]", userInformation);
		 * editor.commit();
		 * 
		 * // 4.登陆成功，进入地图页面 Toast.makeText(LoginActivity.this, "登陆成功！",
		 * Toast.LENGTH_LONG).show();
		 * Intent intent = new Intent(LoginActivity.this,
		 * RegisterActivity.class); startActivity(intent); finish();
		 * 
		 * } });
		 */

		// 添加注册按钮的业务逻辑
		registerButton.setOnClickListener(new View.OnClickListener() {

			@Override
			public void onClick(View view) {
				Intent intent = new Intent(LoginActivity.this, RegisterActivity.class);
				startActivity(intent);
				finish();
			}
		});
	}

}
