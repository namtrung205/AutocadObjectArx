using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using Autodesk.AutoCAD.ApplicationServices;
using Autodesk.AutoCAD.Runtime;

using Autodesk.AutoCAD.EditorInput;
using Autodesk.AutoCAD.Internal.Reactors;

using log4net;

using ObjectArxForDummies.AutocadDotNetAPI.Manager;

namespace ObjectArxForDummies
{
    namespace AutocadDotNetAPI
    {

        //This is EntryPoint of our Application
        //This is used for register event, loading resource, checklicense...etc

        public class AcadEntryPoint : IExtensionApplication
        {
            Document doc = Application.DocumentManager.MdiActiveDocument;
            public void Initialize()
            {
                //App load message
                doc.Editor.WriteMessage("App Loaded Successed!");
                log4net.Config.XmlConfigurator.Configure();
                DocumentManager.Instance.InitReactor();


            }

            public void Terminate()
            {
                //Good Bye
                doc.Editor.WriteMessage("App unLoaded");
            }
        }
    }
}


