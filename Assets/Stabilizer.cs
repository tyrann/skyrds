using UnityEngine;
using System.Collections;

public class Stabilizer : MonoBehaviour {

	// Use this for initialization
	void Start () {
	
	}
	
	// Update is called once per frame
	void FixedUpdate () {
		
		Quaternion rotation = Quaternion.Slerp(transform.localRotation,Quaternion.Euler(new Vector3(0,0,0)),Time.deltaTime * 1);

		transform.localRotation = rotation;
	
	}
}
