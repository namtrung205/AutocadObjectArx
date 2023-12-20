using Autodesk.AutoCAD.ApplicationServices;
using Autodesk.AutoCAD.DatabaseServices;
using Autodesk.AutoCAD.EditorInput;
using Autodesk.AutoCAD.Geometry;
using Autodesk.AutoCAD.Runtime;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using UtcSimpleArxWrapper;
using cadApp = Autodesk.AutoCAD.ApplicationServices.Application;

namespace UtcSimpleCSharpClientApp
{
    public class CsharpClientAppSample
    {

        [CommandMethod("DrawCircle")]
        static public void DoIt()
        {
            MainWindow myWindow = new MainWindow();
            myWindow.Show();
        }

        [CommandMethod("MoveUpObject")]
        static public void MoveUpObject()
        {

            ObjectId id = ObjectId.Null;
            Document acDoc = cadApp.DocumentManager.MdiActiveDocument;
            Database acDb = acDoc.Database;

            PromptSelectionOptions promptOnly = new PromptSelectionOptions();
            // Clear the PickFirst selection set
            // Some time clear selection is wrong
            try
            {
                ObjectId[] idarrayEmpty = Array.Empty<ObjectId>();
                acDoc.Editor.SetImpliedSelection(idarrayEmpty);
            }
            catch (System.Exception ex)
            {
                throw ex;
            }

            promptOnly.SingleOnly = true;
            promptOnly.MessageForAdding = "Chọn 1 đối tượng";
            PromptSelectionResult acSSPrompt;

            acSSPrompt = acDoc.Editor.GetSelection(promptOnly);

            // IF THE PROMPT STATUS IS OK, OBJECTS WERE SELECTED
            if (acSSPrompt != null && acSSPrompt.Status == PromptStatus.OK)
            {

                SelectionSet acSSet = acSSPrompt.Value;
                if (acSSet.Count > 0)
                {
                    id = acSSet[0].ObjectId;
                }
            }

            DBObject selectObject = id.Open(OpenMode.ForRead);

            if (selectObject is Entity)
            {
                Matrix3d inputMat = Matrix3d.Identity;
                //Select an object
                UtcSimpleArxWrapperInterface VithepTowerArxWrapperInterface = new UtcSimpleArxWrapperInterface();

                //Change inputMat by our arx API
                Matrix3d outMat = VithepTowerArxWrapperInterface.MoveUp(inputMat, 100);

                //Implement Move by output Mat
                using (Transaction trans = acDb.TransactionManager.StartTransaction())
                {
                    try
                    {
                        Entity entSelected = trans.GetObject(id, OpenMode.ForWrite) as Entity;

                        if (entSelected != null)
                        {
                            entSelected.TransformBy(outMat);
                            trans.Commit();
                        }

                    }
                    catch (System.Exception ex)
                    {
                        trans.Abort();
                    }
                }

            }
        }


        [CommandMethod("PlaceSmiley")]
        static public void PlaceSmiley()
        {

            UtcSimpleArxWrapperInterface vithepTowerArxWrapperInterface = new UtcSimpleArxWrapperInterface();
            vithepTowerArxWrapperInterface.PlaceSmiley();
        }

        [CommandMethod("PlaceSmileyUI")]
        static public void PlaceSmileyUI()
        {

            SmileyWindow myWindow = new SmileyWindow();
            myWindow.Show();
        }

    }
}
