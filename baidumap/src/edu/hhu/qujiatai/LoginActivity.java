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
	 * 1.�ڲ����ļ��и���Ҫ��Java�����в����Ŀؼ�ȡΨһ��idֵ 2.��Activity���������Ϳؼ���Ӧ�ĳ�Ա����
	 * 3.�������ļ��еĿؼ���Activity�еĳ�Ա�������а�
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

	// ��ʼ��
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

	// ����¼�����
	private void addAction() {

		// ��ס�˺Ÿ�ѡ����ӵ��������¼�
		rememberAccountCheckBox.setOnCheckedChangeListener(new CompoundButton.OnCheckedChangeListener() {
			@Override
			public void onCheckedChanged(CompoundButton compoundButton, boolean flag) {
				if (flag) {
				} else {
					rememberPasswordCheckBox.setChecked(false);
				}
			}

		});
		// ��ס���븴ѡ����ӵ��������¼�
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
					Toast.makeText(LoginActivity.this, account + "�˺Ų����ڣ�", Toast.LENGTH_LONG).show();
					return;
				}
				String[] userInformationArray = userInformation.split(SPL);
				if (!password.equals(userInformationArray[0])) {
					Toast.makeText(LoginActivity.this, "�������", Toast.LENGTH_LONG).show();
					return;
				}

				Toast.makeText(LoginActivity.this, "��¼�ɹ�!", 3000).show();
				Intent intent = new Intent(LoginActivity.this, BaiduMapActivity.class);
				startActivity(intent);
				finish();
			}
		});

		/*
		 * // ��ӵ�¼��ť��ҵ���߼� loginButton.setOnClickListener(new
		 * View.OnClickListener() {
		 * 
		 * @Override public void onClick(View view) { // 1.��ȡ�û���������˺ź������ֵ
		 * String account = accountEditText.getText().toString().trim(); String
		 * password = passwordEditText.getText().toString().trim(); //
		 * 2.�����˺ź�����ıȽϣ�demo��
		 * 
		 * if (account.equals("qujiatai") && password.equals("123456")) {
		 * Toast.makeText(LoginActivity.this, "��½�ɹ���\n�����ͼ��ҳ��",
		 * Toast.LENGTH_LONG).show(); } else {
		 * Toast.makeText(LoginActivity.this, "�˺Ż��������",
		 * Toast.LENGTH_LONG).show(); }
		 * 
		 * // 2.�����˺ź�����ıȽϣ���ʵ���ݣ� String userInformation = sp.getString(account,
		 * ""); if (userInformation.equals("")) {
		 * Toast.makeText(LoginActivity.this, account + "�˺Ų����ڣ�",
		 * Toast.LENGTH_LONG).show(); return; } String[] userInformationArray =
		 * userInformation.split(SPL);
		 * 
		 * if (!password.equals(userInformationArray[0])) {
		 * Toast.makeText(LoginActivity.this, "�������",
		 * Toast.LENGTH_LONG).show(); return; } //
		 * �����µļ�ס�˺źͼ�ס�����״̬���µ�baidumap.xml�ļ��� String rememberStatus = ""; if
		 * (!rememberAccountCheckBox.isChecked() &&
		 * !rememberPasswordCheckBox.isChecked()) { rememberStatus = "0_0"; } if
		 * (rememberAccountCheckBox.isChecked() &&
		 * rememberPasswordCheckBox.isChecked()) { rememberStatus = "1_1"; } if
		 * (rememberAccountCheckBox.isChecked() &&
		 * !rememberPasswordCheckBox.isChecked()) { rememberStatus = "1_0"; }
		 * userInformation = userInformation.replace(userInformationArray[1],
		 * rememberStatus);
		 * 
		 * // 3.����ǰ��¼���˺ű������� editor.putString("currentAccount", account);
		 * editor.putString("userInformationArray[1]", userInformation);
		 * editor.commit();
		 * 
		 * // 4.��½�ɹ��������ͼҳ�� Toast.makeText(LoginActivity.this, "��½�ɹ���",
		 * Toast.LENGTH_LONG).show();
		 * Intent intent = new Intent(LoginActivity.this,
		 * RegisterActivity.class); startActivity(intent); finish();
		 * 
		 * } });
		 */

		// ���ע�ᰴť��ҵ���߼�
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
