﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ObjectArxForDummies
{
    namespace AutocadDotNetAPI.Loger
    {

        internal class DummiesLoger
        {
            public static readonly log4net.ILog Log = log4net.LogManager.GetLogger
                    (System.Reflection.MethodBase.GetCurrentMethod().DeclaringType);

        }
    }
}