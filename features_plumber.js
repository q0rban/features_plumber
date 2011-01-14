// $Id$

/**
 * @file
 * Features Plumber js.
 */

Drupal.behaviors.featuresPlumber = function(context) {
  $('#features-export-populated', context).after('<div id="features-plumber"></div>');
  // By not filtering to context, this will call every time.
  $('#features-export-populated .features-plumber-plumbable').each(function () {
    var item = $(this);
    var component = item.attr('component');
    var componentVal = item.attr('component_val');
    $('#features-export-form input[component="' + component + '"][component_val="' + componentVal + '"]').prependTo(item).show();
  });
}