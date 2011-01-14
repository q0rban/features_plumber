// $Id$

/**
 * @file
 * Features Plumber js.
 */

Drupal.behaviors.featuresPlumber = function(context) {
  // By not filtering to context, we can manipulate these.
  $('#features-export-populated .features-plumber-plumbable').each(function () {
    var item = $(this);
    var component = item.attr('component');
    var componentVal = item.attr('component_val');
    $('#features-export-form input[component="' + component + '"][component_val="' + componentVal + '"]').prependTo(item).show();
  });
}