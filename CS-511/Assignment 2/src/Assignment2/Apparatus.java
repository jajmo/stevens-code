package Assignment2;

import java.util.HashMap;
import java.util.Map;

public class Apparatus {
	public static Map<ApparatusType, String> strings = new HashMap<ApparatusType, String>();
	
	public enum ApparatusType {
		 LEGPRESSMACHINE, BARBELL, HACKSQUATMACHINE, LEGEXTENSIONMACHINE,
		 LEGCURLMACHINE, LATPULLDOWNMACHINE, PECDECKMACHINE,
		 CABLECROSSOVERMACHINE;
		
		public static ApparatusType getRandom() {
			return values()[(int) (Math.random() * values().length)];
		}
	 };
	 
	 public static void populateMap() {
		 strings.put(ApparatusType.LEGPRESSMACHINE, "leg press machine");
		 strings.put(ApparatusType.BARBELL, "barbell");
		 strings.put(ApparatusType.HACKSQUATMACHINE, "hack squat machine");
		 strings.put(ApparatusType.LEGEXTENSIONMACHINE, "leg extension machine");
		 strings.put(ApparatusType.LEGCURLMACHINE, "leg curl machine");
		 strings.put(ApparatusType.LATPULLDOWNMACHINE, "lat pulldown machine");
		 strings.put(ApparatusType.PECDECKMACHINE, "pec deck machine");
		 strings.put(ApparatusType.CABLECROSSOVERMACHINE, "cable crossover machine");
	 }
}
