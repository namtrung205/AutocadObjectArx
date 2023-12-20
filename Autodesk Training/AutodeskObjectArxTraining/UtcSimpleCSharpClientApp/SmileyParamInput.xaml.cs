using System;
using System.Collections.Generic;
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
using UtcSimpleArxWrapper;
namespace UtcSimpleCSharpClientApp
{
    /// <summary>
    /// Interaction logic for UserControl1.xaml
    /// </summary>
    public partial class SmileyWindow : Window
    {
        public SmileyWindow()
        {
            InitializeComponent();
        }

        private void Button_Click(object sender, RoutedEventArgs e)
        {
            double faceSize = Convert.ToDouble(faceSizeTb.Text);
            double eyeSize = Convert.ToDouble(eyeSizeTb.Text);
            this.Close();
            if (faceSize > 0)
            {
                UtcSimpleArxWrapperInterface utcSimpleArxWrapperInterface = new UtcSimpleArxWrapperInterface();
                utcSimpleArxWrapperInterface.PlaceSmiley(faceSize, eyeSize);
            }

            
        }
    }
}
