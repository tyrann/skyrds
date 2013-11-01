using UnityEngine;
using System.Collections;

public class SuspensionRay : MonoBehaviour
{
	float suspensionRange = 1.7f;
	float suspensionForce = 900f;
	float suspensionDamp = 60.00f;
	bool hasLift=false;
	private RaycastHit hit;
	private Rigidbody parent;


	void FixedUpdate ()
	{	
		GameObject levelParent = GameObject.FindGameObjectWithTag ("Player");
		parent = transform.root.rigidbody;
		Vector3 down = transform.TransformDirection (Vector3.down);
		Vector3 worldDown = levelParent.transform.TransformDirection (Vector3.down);
		if (Physics.Raycast (transform.position, worldDown, out hit, suspensionRange) && hit.collider.transform.root != transform.root) {
			hasLift=true;
			Vector3 velocityAtTouch = parent.GetPointVelocity (hit.point);
//			suspensionForce = 500 * 1/hit.distance;
			float compression = hit.distance / (suspensionRange);
			compression = -compression + 1;
			Vector3 counterForce = (-worldDown * compression * suspensionForce);
			Vector3 t = transform.InverseTransformDirection (velocityAtTouch);
			t.z = t.x = 0;
			Vector3 shockDrag = levelParent.transform.TransformDirection (t) * -suspensionDamp;
			parent.AddForceAtPosition (counterForce + shockDrag, hit.point);
		}
		//helps keeps the ship steady around the Y-axis
		 levelParent.transform.localRotation = Quaternion.Euler(transform.rotation.eulerAngles.x, 0, transform.rotation.eulerAngles.z);
	}

	// Use this for initialization
	void Start ()
	{

	}

	// Show yellow Rays
	void OnDrawGizmos ()
	{
		GameObject levelParent = GameObject.FindGameObjectWithTag ("Player");
		Gizmos.color = Color.yellow;
		Gizmos.DrawRay (transform.position, levelParent.transform.TransformDirection (Vector3.up) * -suspensionRange);
		Gizmos.color=Color.white;
		Gizmos.DrawWireSphere(transform.position,0.4f);
	}
}