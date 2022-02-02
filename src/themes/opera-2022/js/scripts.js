window.onscroll = function changeClass(){
	var navBar = document.getElementsByClassName('l-header');
	var layoutHeight = document.querySelector(".layout").offsetHeight;
	let windowHeight = window.innerHeight;
	var scrollPosY = window.pageYOffset | document.body.scrollTop;

	if (document.querySelector("#admin-bar") !== null) {
		var adminBarHeight = document.querySelector("#admin-bar").offsetHeight;
	} else {
		var adminBarHeight = 0;
	}
	

	if (adminBarHeight > 1) {
		adminBarHeight = document.querySelector("#admin-bar").offsetHeight;
	} else {
		adminBarHeight = 100;
	}

	if(scrollPosY > adminBarHeight) {
		navBar[0].classList.add('sticky_header');
	} else if(scrollPosY <= adminBarHeight) {
		navBar[0].classList.remove('sticky_header');
	}
}