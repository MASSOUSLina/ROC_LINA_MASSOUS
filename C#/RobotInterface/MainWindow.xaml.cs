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

namespace RobotInterface
{
    /// <summary>
    /// Logique d'interaction pour MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        ReliableSerialPort serialPort1;

        void envoyer()
        {
            textBoxReception.Text = textBoxReception.Text + "reçu: " + textBoxEmission.Text + "\n";
            textBoxEmission.Clear();

        }
        public MainWindow()
        {
            InitializeComponent();
            serialPort1 = new ReliableSerialPort("COM3", 115200, Parity.None, 8, StopBits.One);
            serialPort1.Open();
        }

        private void buttonEnvoyer_Click(object sender, RoutedEventArgs e)
        {
            buttonEnvoyer.Background = Brushes.Beige;
            envoyer();
        }

        private void buttonEnvoyer_KeyUp(object sender, KeyEventArgs e)
        {
            if (e.Key == Key.Enter)
            {
                envoyer();
            }
        }
       
    }
}
