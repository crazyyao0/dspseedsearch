# -*- coding: utf-8 -*-
from bs4 import BeautifulSoup


bs = BeautifulSoup(open("ThemeProtoSet.xml", encoding="utf-8"), features="xml")
for t in bs.find_all("ThemeProto"):
    fields = []
    fields.append('"%s", %s, "%s", EPlanetType::%s, %s, EThemeDistribute::%s'%(t.Name.text, t.ID.text, t.DisplayName.text, t.PlanetType.text, t.Temperature.text, t.Distribute.text))
    fields.append("{" + ", ".join([c.text for c in t.Algos.find_all("int")]) + "}")
    fields.append("{%s, %s}, {%s, %s}"%(t.ModX.x.text, t.ModX.y.text, t.ModY.x.text, t.ModY.y.text))
    fields.append("{" + ", ".join([c.text for c in t.VeinSpot.find_all("int")]) + "}")
    fields.append("{" + ", ".join([c.text for c in t.VeinCount.find_all("float")]) + "}")
    fields.append("{" + ", ".join([c.text for c in t.VeinOpacity.find_all("float")]) + "}")
    fields.append("{" + ", ".join([c.text for c in t.RareVeins.find_all("int")]) + "}")
    fields.append("{" + ", ".join([c.text for c in t.RareSettings.find_all("float")]) + "}")
    fields.append("{" + ", ".join([c.text for c in t.GasItems.find_all("int")]) + "}")
    fields.append("{" + ", ".join([c.text for c in t.GasSpeeds.find_all("float")]) + "}")
    fields.append('%s, %s, %s, %s, %s'%(t.UseHeightForBuild.text, t.Wind.text, t.IonHeight.text, t.WaterHeight.text, t.WaterItemId.text))
    print("themes.push_back({ " + ", ".join(fields) + "});")