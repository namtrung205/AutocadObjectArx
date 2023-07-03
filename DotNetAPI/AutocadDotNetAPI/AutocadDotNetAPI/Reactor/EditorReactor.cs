using Autodesk.AutoCAD.ApplicationServices;
using Autodesk.AutoCAD.Runtime;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ObjectArxForDummies
{
    namespace AutocadDotNetAPI.Reactor
    {
        public class EditorReactor
        {
            Document doc = Autodesk.AutoCAD.ApplicationServices.Core.Application.DocumentManager.MdiActiveDocument;
            public EditorReactor()
            {
                doc.CommandEnded += Doc_CommandEnded;
            }

            private void Doc_CommandEnded(object sender, CommandEventArgs e)
            {
                var commandName = e.GlobalCommandName;

                
            }
        }
    }

}
