using UnityEngine;
using System.Collections;

public class CameraControl : MonoBehaviour
{
	GameObject camera;
	// Use this for initialization
	void Start ()
	{
		camera=gameObject;
		camera.transform.eulerAngles = new Vector3(9, 0, 0);
	
	}
	
	// Update is called once per frame
	void Update ()
	{
		float DistanceAway = 10.5f;
		Vector3 PlayerPOS = GameObject.FindGameObjectWithTag ("Player").transform.transform.position;
		camera.transform.position = new Vector3 (PlayerPOS.x, 1.587326f+PlayerPOS.y, PlayerPOS.z - DistanceAway);
	}
}
