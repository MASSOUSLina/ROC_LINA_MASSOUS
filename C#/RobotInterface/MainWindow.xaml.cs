using ExtendedSerialPort;
using System;
using System.Collections.Generic;
using System.IO.Ports;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.Windows.Threading ;
namespace RobotInterface
{
    /// <summary>
    /// Logique d'interaction pour MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        ReliableSerialPort serialPort1;
        DispatcherTimer timerAffichage ;
        void envoyer()
        {
            serialPort1.WriteLine(textBoxEmission.Text);
            //textBoxReception.Text = textBoxReception.Text + "reçu: " + textBoxEmission.Text + "\n";
            textBoxEmission.Clear();
        }        

        public MainWindow()
        {
            InitializeComponent();
            serialPort1 = new ReliableSerialPort("COM10", 115200, Parity.None, 8, StopBits.One);
            serialPort1.DataReceived += SerialPort1_DataReceived;
            serialPort1.Open();
            timerAffichage = new DispatcherTimer();
            timerAffichage.Interval = new TimeSpan(0, 0, 0, 0, 100);
            timerAffichage.Tick += TimerAffichage_Tick;
            timerAffichage.Start();
            Robot robot=new Robot();
        }

        private void TimerAffichage_Tick(object sender, EventArgs e)
        {
            if(robot.receivedText != "")
            {
                textBoxReception.Text += robot.receivedText;
                robot.receivedText = "";
            }
        }

        private void SerialPort1_DataReceived(object sender, DataReceivedArgs e)
        {
            //throw new NotImplementedException();
            robot.receivedText += Encoding.UTF8.GetString(e.Data, 0, e.Data.Length);

        }

        private void buttonEnvoyer_Click(object sender, RoutedEventArgs e)
        {
            buttonEnvoyer.Background = Brushes.Beige;
            envoyer();
        }
        private void textBoxEmission_KeyUp(object sender, KeyEventArgs e)
        {
            if (e.Key == Key.Enter)
            {
                envoyer();
            }
        }

        private void ButtonClear_Click(object sender, RoutedEventArgs e)
        {
            buttonClear.Background = Brushes.Beige;

            textBoxReception.Clear();
        }
    }
}
