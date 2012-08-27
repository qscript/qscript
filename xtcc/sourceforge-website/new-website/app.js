jQuery(function() {
	//alert("jQuery alive");
$('.bs-docs-sidenav').affix({
      offset: {
        //top: function () { return $window.width() <= 980 ? 290 : 210 }
	top: 0
      , bottom: 270
      }
});

    $('.tooltip-demo').tooltip({
      selector: "a[rel=tooltip]"
    })
    $('.code-tooltip').tooltip({
      selector: "a[rel=tooltip]"
    })


});
