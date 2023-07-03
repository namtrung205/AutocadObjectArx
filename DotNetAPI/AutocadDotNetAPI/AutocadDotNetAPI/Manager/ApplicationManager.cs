using Autodesk.AutoCAD.ApplicationServices;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ObjectArxForDummies.AutocadDotNetAPI.Manager
{
    public class ApplicationManager
    {
        public ApplicationManager()
        {
            if (ActiveAcadDocument == null)
            {
                ActiveAcadDocument = Application.DocumentManager.MdiActiveDocument;

            }
        }


        public static Document ActiveAcadDocument { get; set; }


        //Singleton
        #region Fields
        private static ApplicationManager _instance;

        #endregion

        #region Properties
        public static ApplicationManager Instance
        {

            get
            {
                if (_instance == null)
                {
                    _instance = new ApplicationManager();
                }
                return _instance;
            }
            set
            {
                _instance = value;
            }
        }
        #endregion


        public void InitReactor()
        {
            if (ActiveAcadDocument != null)
            {
                ActiveAcadDocument.CommandEnded += ActiveAcadDocument_CommandEnded;

            }


        }


        #region Event/ Reactor

        //Reactor / Events
        private void ActiveAcadDocument_CommandEnded(object sender, CommandEventArgs e)
        {
            if (ActiveAcadDocument != null)
            {
                ActiveAcadDocument.Editor.WriteMessage(e.GlobalCommandName);

            }
        }
        #endregion


    }

}

